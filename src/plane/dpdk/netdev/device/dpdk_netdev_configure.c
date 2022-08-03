/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include "dpdk_netdev_configure.h"
#include "../../plane_dpdk_utils.h"
#include "../../../plane_utils.h"
#include "../../dpdk_inc.h"


static uint16_t __get_dpdk_netdev_cfg_rx_desc_nr(void)
{
    plane_dpdk_t                *dpdk;

    dpdk = __get_plane_dpdk();

    return dpdk->netdev->cfg.rx_desc;
}

static uint16_t __get_dpdk_netdev_cfg_tx_desc_nr(void)
{
    plane_dpdk_t                *dpdk;

    dpdk = __get_plane_dpdk();

    return dpdk->netdev->cfg.tx_desc;
}

static struct rte_mempool *__get_dpdk_percpu_mempool(uint16_t id)
{
    dpdk_percpu_block_t         *percpu_block;
    plane_dpdk_t                *dpdk;

    dpdk = __get_plane_dpdk();

    percpu_block = dpdk->percpu->ops->get_percpu_block(id);

    ASSERT(percpu_block && percpu_block->id==id);
    ASSERT(percpu_block->mbuf_pool);

    return percpu_block->mbuf_pool;
}

static int _dpdk_netdev_configure_rx_queue(uint16_t port_id, uint16_t queue_nr, 
        struct rte_eth_dev_info *dev_info, struct rte_eth_rxconf *rxq_conf, uint16_t rx_desc_nr)
{
    uint16_t                    i;
    int                         socket_id, ret;

    socket_id  = rte_eth_dev_socket_id(port_id);

    for (i=0; i<queue_nr; ++i) {

        //use per-cpu's pool
        ret = rte_eth_rx_queue_setup(port_id, i, rx_desc_nr, socket_id, 
                rxq_conf, __get_dpdk_percpu_mempool(i));

        if (ret < 0) {
            LOGE("rte_eth_rx_queue_setup error=%d, queue=%u", ret, i);
            return -1;
        }

        LOGD("rte_eth_rx_queue_setup port=%u, queue=%u, ret=%d", port_id, i, ret);
    }
    
    return 0;
}

static int _dpdk_netdev_configure_tx_queue(uint16_t port_id, uint16_t queue_nr, 
        struct rte_eth_dev_info *dev_info, struct rte_eth_txconf *txq_conf, uint16_t tx_desc_nr)
{
    uint16_t                    i;
    int                         socket_id, ret;

    socket_id  = rte_eth_dev_socket_id(port_id);

    for (i=0; i<queue_nr; ++i) {

        ret = rte_eth_tx_queue_setup(port_id, i, tx_desc_nr, socket_id,
                txq_conf);

        if (ret < 0) {
            LOGE("rte_eth_tx_queue_setup error=%d, queue=%u", ret, i);
            return -1;
        }

        LOGD("rte_eth_tx_queue_setup port=%u, queue=%u, ret=%d", port_id, i, ret);
    }

    return 0;
}

static int _dpdk_netdev_configure_dev(uint16_t port_id, uint16_t queue_nr, 
        struct rte_eth_conf *conf, struct rte_eth_dev_info *dev_info)
{
    int                     ret;

    if (dev_info->tx_offload_capa & DEV_TX_OFFLOAD_MBUF_FAST_FREE) {
        conf->txmode.offloads |= DEV_TX_OFFLOAD_MBUF_FAST_FREE;
    }

    /*
     * The backgroud of this code:
     *
     * VirtIO: virtio does not support RSS settings (It has default RSS)
     * HW    : But HW device need to set up RSS to be enable
     *
     */
	if (strcmp(dev_info->driver_name, "net_virtio")) {
		conf->rxmode.mq_mode              = ETH_MQ_RX_RSS;
		conf->rx_adv_conf.rss_conf.rss_hf = ETH_RSS_IPV4 | ETH_RSS_NONFRAG_IPV4_TCP | \
			ETH_RSS_NONFRAG_IPV4_UDP;
	}

    ret = rte_eth_dev_configure(port_id, queue_nr, queue_nr, conf);

    if (ret < 0) {
        LOGE("rte_eth_dev_configure error=%d, queue_nr=%u, port=%d", ret, queue_nr, port_id);
        return -1;
    }

    return ret;
}

static int _dpdk_netdev_configure_hw(uint16_t port_id, uint16_t queue_nr, 
        struct rte_eth_dev_info *dev_info)
{
    struct rte_eth_conf         conf = {
        .rxmode = {
            .max_rx_pkt_len = RTE_ETHER_MAX_LEN,
        },
    };

    int                         ret;
    struct rte_eth_rxconf       rxq_conf;
    struct rte_eth_txconf       txq_conf;
    uint16_t                    rx_desc_nr;
    uint16_t                    tx_desc_nr;


    if (_dpdk_netdev_configure_dev(port_id, queue_nr, &conf, dev_info) < 0) {
        return -1;
    }

    rx_desc_nr = __get_dpdk_netdev_cfg_rx_desc_nr();
    tx_desc_nr = __get_dpdk_netdev_cfg_tx_desc_nr();

    ret = rte_eth_dev_adjust_nb_rx_tx_desc(port_id, &rx_desc_nr, &tx_desc_nr);
    if (ret < 0) {
        LOGE("rte_eth_dev_adjust_nb_rx_tx_desc error=%d", ret);
        return -1;
    }
    LOGD("rte_eth_dev_adjust_nb_rx_tx_desc rx_desc %u, tx_desc %u", rx_desc_nr, tx_desc_nr);


    txq_conf = dev_info->default_txconf;
    txq_conf.offloads = conf.txmode.offloads;

    rxq_conf = dev_info->default_rxconf;
    rxq_conf.offloads = conf.rxmode.offloads;

    ret = _dpdk_netdev_configure_rx_queue(port_id, queue_nr, dev_info, &rxq_conf, rx_desc_nr);
    if (ret < 0) {
        return -1;
    }

    ret = _dpdk_netdev_configure_tx_queue(port_id, queue_nr, dev_info, &txq_conf, tx_desc_nr);
    if (ret < 0) {
        return -1;
    }

    return 0;
}


static int _dpdk_netdev_evaluate_queue_nr(uint16_t *queue_nr, struct rte_eth_dev_info *dev_info)
{
    uint16_t                    cpu_nr;
    uint16_t                    max_queue_nr;

    cpu_nr = __plane_get_worker_nr();

    /*
     * max_queue_nr is the min of rx and tx
     */
    max_queue_nr = dev_info->max_rx_queues > dev_info->max_tx_queues ?
        dev_info->max_tx_queues : dev_info->max_rx_queues;

    LOGW("mas support queue_nr: %u, cpu_nr: %u", max_queue_nr, cpu_nr);
    if (cpu_nr > max_queue_nr) {
        LOGE("dpdk port max_queue=%u, but used number of cpu=%u", max_queue_nr, cpu_nr);
        return -1;
    }

    /*
     * How many cpu, how many queue.
     */
    *queue_nr = cpu_nr;

    return 0;
}


int dpdk_netdev_configure(plane_dpdk_netdev_t *netdev)
{
    struct rte_eth_dev_info     dev_info;
    uint16_t                    queue_nr;
    uint16_t                    port_id;

    port_id = netdev->port_id;

    if (rte_eth_dev_info_get(port_id, &dev_info) < 0) {
        LOGE("rte_eth_dev_info_get failed!");
        return -1;
    }

    if (_dpdk_netdev_evaluate_queue_nr(&queue_nr, &dev_info) < 0) {
        return -1;
    }

    netdev->queue_nr = queue_nr;

    return _dpdk_netdev_configure_hw(port_id, queue_nr, &dev_info);
}
