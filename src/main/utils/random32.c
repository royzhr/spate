/*
  Copy from ancient-linux-kernel


  This is a maximally equidistributed combined Tausworthe generator
  based on code from GNU Scientific Library 1.5 (30 Jun 2004)

   x_n = (s1_n ^ s2_n ^ s3_n)

   s1_{n+1} = (((s1_n & 4294967294) <<12) ^ (((s1_n <<13) ^ s1_n) >>19))
   s2_{n+1} = (((s2_n & 4294967288) << 4) ^ (((s2_n << 2) ^ s2_n) >>25))
   s3_{n+1} = (((s3_n & 4294967280) <<17) ^ (((s3_n << 3) ^ s3_n) >>11))

   The period of this generator is about 2^88.

   From: P. L'Ecuyer, "Maximally Equidistributed Combined Tausworthe
   Generators", Mathematics of Computation, 65, 213 (1996), 203--213.

   This is available on the net from L'Ecuyer's home page,

   http://www.iro.umontreal.ca/~lecuyer/myftp/papers/tausme.ps
   ftp://ftp.iro.umontreal.ca/pub/simulation/lecuyer/papers/tausme.ps

   There is an erratum in the paper "Tables of Maximally
   Equidistributed Combined LFSR Generators", Mathematics of
   Computation, 68, 225 (1999), 261--269:
   http://www.iro.umontreal.ca/~lecuyer/myftp/papers/tausme2.ps

        ... the k_j most significant bits of z_j must be non-
        zero, for each j. (Note: this restriction also applies to the
        computer code given in [4], but was mistakenly not mentioned in
        that paper.)

   This affects the seeding procedure by imposing the requirement
   s1 > 1, s2 > 7, s3 > 15.

*/

#include <spate_core.h>
#include <utils/random32.h>


struct rnd_state {
	uint32_t s1, s2, s3;
};


static struct rnd_state g_rand_state;


static uint32_t __random32(struct rnd_state *state)
{
#define TAUSWORTHE(s,a,b,c,d) ((s&c)<<d) ^ (((s <<a) ^ s)>>b)

	state->s1 = TAUSWORTHE(state->s1, 13, 19, 4294967294UL, 12);
	state->s2 = TAUSWORTHE(state->s2, 2, 25, 4294967288UL, 4);
	state->s3 = TAUSWORTHE(state->s3, 3, 11, 4294967280UL, 17);

	return (state->s1 ^ state->s2 ^ state->s3);
}

static void __set_random32(struct rnd_state *state, unsigned long s)
{
	if (s == 0)
		s = 1;      /* default seed is 1 */

#define LCG(n) (69069 * n)
	state->s1 = LCG(s);
	state->s2 = LCG(state->s1);
	state->s3 = LCG(state->s2);

	/* "warm it up" */
	__random32(state);
	__random32(state);
	__random32(state);
	__random32(state);
	__random32(state);
	__random32(state);
}

/**
 *	random32 - pseudo random number generator
 *
 *	A 32 bit pseudo-random number is generated using a fast
 *	algorithm suitable for simulation. This algorithm is NOT
 *	considered safe for cryptographic use.
 */
uint32_t random32(void)
{
	unsigned long r;
	struct rnd_state *state = &g_rand_state;
	r = __random32(state);
	return r;
}

/**
 *	srandom32 - add entropy to pseudo random number generator
 *	@seed: seed value
 *
 *	Add some additional seeding to the random32() pool.
 */
void srandom32(uint32_t entropy)
{
    struct rnd_state *state = &g_rand_state;

    __set_random32(state, state->s1 ^ entropy);
}

/*
 *	Generate some initially weak seeding values to allow
 *	to start the random32() engine.
 */
int random32_init(unsigned long seed)
{
    struct rnd_state *state = &g_rand_state;

    __set_random32(state, seed);
    return 0;
}

