#
# Rodzhang
#
# DPDK's make
#


#DPDK_OBJ_DIR = $(foreach dir, $(DPDK_SRC_DIR), $(addprefix build/, $(dir)))
#DPDK_SRC_C = $(foreach dir, $(DPDK_SRC_DIR), $(wildcard $(dir)/*.c))
#DPDK_OBJECT = $(addprefix build/, $(patsubst %.c, %.o, $(DPDK_SRC_C)))


PKGCONF ?= pkg-config

DPDK_CFLAGS = $(shell $(PKGCONF) --cflags libdpdk)
# Added for 'rte_eth_link_to_str()'
DPDK_CFLAGS += -DALLOW_EXPERIMENTAL_API


DPDK_DEP_LIBS = $(shell $(PKGCONF) --static --libs libdpdk)


