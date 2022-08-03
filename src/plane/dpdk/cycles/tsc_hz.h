/*
 * Rodzhang
 *
 */

#ifndef __TSC_HZ_H__
#define __TSC_HZ_H__


#include <spate_core.h>
#include <time.h>


static inline uint64_t __spate_rdtsc(void)
{
    union {
        uint64_t tsc_64;
        struct {
            uint32_t lo_32;
            uint32_t hi_32;
        };
    } tsc;

    asm volatile("rdtsc" :
            "=a" (tsc.lo_32),
            "=d" (tsc.hi_32));

    return tsc.tsc_64;
}



#define TSC_ALIGN_MUL_CEIL(v, mul) \
	((((v) + (typeof(v))(mul) - 1) / ((typeof(v))(mul))) * (typeof(v))(mul))


#define TSC_ALIGN_MUL_FLOOR(v, mul) \
	(((v) / ((typeof(v))(mul))) * (typeof(v))(mul))


#define TSC_ALIGN_MUL_NEAR(v, mul)				\
	({							\
		typeof(v) ceil = TSC_ALIGN_MUL_CEIL(v, mul);	\
		typeof(v) floor = TSC_ALIGN_MUL_FLOOR(v, mul);	\
		(ceil - (v)) > ((v) - floor) ? floor : ceil;	\
	})


static inline uint64_t __spate_get_hz(void)
{
#define NS_PER_SEC 1E9
#define CYC_PER_10KHZ 1E4

	struct timespec sleeptime = {.tv_nsec = NS_PER_SEC / 10 }; /* 1/10 second */

	struct timespec t_start, t_end;
	uint64_t tsc_hz;

	if (clock_gettime(CLOCK_MONOTONIC_RAW, &t_start) == 0) {
		uint64_t ns, end, start = __spate_rdtsc();

		nanosleep(&sleeptime, NULL);
		clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);
		end = __spate_rdtsc();
		ns = ((t_end.tv_sec - t_start.tv_sec) * NS_PER_SEC);
		ns += (t_end.tv_nsec - t_start.tv_nsec);

		double secs = (double)ns/NS_PER_SEC;
		tsc_hz = (uint64_t)((end - start)/secs);
		/* Round up to 10Khz. 1E4 ~ 10Khz */
		return TSC_ALIGN_MUL_NEAR(tsc_hz, CYC_PER_10KHZ);
	}

    return 0;
}


#endif /* __TSC_HZ_H__ */
