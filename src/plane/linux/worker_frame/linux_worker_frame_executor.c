/*
 * Rodzhang
 *
 */

#include "linux_worker_frame_executor.h"
#include "linux_worker_frame_bind_cpu.h"


int linux_worker_frame_executor(plane_linux_worker_frame_t *wf, 
        int (*fn)(void *arg))
{
    uint16_t                        worker_id;
    linux_worker_thread_t           *wt;

    for (worker_id=1; worker_id<wf->cfg.worker_nr; ++worker_id) {
        wt = &wf->worker_threads[worker_id];

        if (pthread_create(&wt->thread, NULL, (void*(*)(void *))fn, 
                    (void*)(intptr_t)worker_id) < 0) {

            LOGE("linux worker frame startup thread eror: worker_id=%u", worker_id);
            return -1;
        }

        LOGD("worker frame create thread %lu", wt->thread);
    }

    /*
     * Bind cpu
     */
    if (linux_worker_frame_bind_cpu(wf) < 0) {
        LOGE("linux worker frame bind cpu error");
        return -1;
    }

    /*
     * Run worker 0
     */
    worker_id = 0;

    fn((void*)(intptr_t)worker_id); 

    return 0;
}

void linux_worker_frame_executor_wait(plane_linux_worker_frame_t *wf)
{
    uint16_t                        worker_id;

    for (worker_id=1; worker_id<wf->cfg.worker_nr; ++worker_id) {

        pthread_join(wf->worker_threads[worker_id].thread, NULL);
    }
}
