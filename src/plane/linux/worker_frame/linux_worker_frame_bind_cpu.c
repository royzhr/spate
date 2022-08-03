/*
 * Rodzhang
 *
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sched.h>

#include "linux_worker_frame_bind_cpu.h"


static int _linux_bind_process_to_cpu(pid_t pid, uint16_t cpu_id)
{
    cpu_set_t                       set;
    int                             ret;

    CPU_ZERO(&set);
    CPU_SET(cpu_id, &set);

    ret = sched_setaffinity(pid, sizeof(set), &set);

    LOGD("bind pid %lu to cpu %u, ret=%d, errno=%d", pid, cpu_id, ret, errno);

    return ret;
}

static int _linux_bind_thread_to_cpu(pthread_t thread, uint16_t cpu_id)
{
    cpu_set_t                       set;
    int                             ret;

    CPU_ZERO(&set);
    CPU_SET(cpu_id, &set);

    ret = pthread_setaffinity_np(thread, sizeof(set), &set);

    LOGD("bind thread %lu to cpu %u, ret=%d, errno=%d", thread, cpu_id, ret, errno);

    return ret;
}


int linux_worker_frame_bind_cpu(plane_linux_worker_frame_t *wf)
{
    uint16_t                        worker_id;
    uint16_t                        cpu_begin, cpu_id;

    if (!wf->cfg.bind_cpu_enable) {
        return 0;
    }

    cpu_begin = wf->cfg.bind_cpu_begin;

    /*
     * Bind worker (thread)
     */
    for (worker_id=1; worker_id<wf->cfg.worker_nr; ++worker_id) {
        cpu_id = cpu_begin + worker_id;

        if (_linux_bind_thread_to_cpu(wf->worker_threads[worker_id].thread, cpu_id) < 0) {
            return -1;
        }
        
    }

    /*
     * Bind worker 0 (process)
     */
    return _linux_bind_process_to_cpu(getpid(), cpu_begin);
}

