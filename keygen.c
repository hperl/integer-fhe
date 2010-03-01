/*
 *  keygen.c
 *  integer-fhe
 *
 *  Created by Henning Perl on 01.03.10.
 *
 */

#include "keygen.h"

void die(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

int keyGen(int lambda)
{
	int i;
	// init random number generator
	gmp_randstate_t randstate;
	gmp_randinit_default(randstate);
	gmp_randseed_ui(randstate, time(NULL));
	
	
	mpz_t p;
	genP(p, &randstate);
	mpz_t q[TAU];
	genQ(q, p, &randstate);
	
	
	/*************** public key part r ****************************************/
	
	// DEBUG output
	for (i=0; i<GAMMA; i++) { gmp_printf("q[%i] = %Zd\n", i, q[i]);	}
	gmp_printf("p = %Zd\n", p);
	
	// TODO: Error detection: What can go wrong?
	return(EXIT_SUCCESS);
}


/********** Helper Methods ***********/
// Helper for keyGen
void genP(mpz_t p, gmp_randstate_t* randstate)
{
	// temp container
	mpz_t temp;
	mpz_init(temp);
	// p_lower = 2^(ETA-1)
	mpz_t p_lower;
	mpz_init(p_lower);
	mpz_ui_pow_ui(p_lower, 2, ETA-1);
	// p_upper = 2^(ETA)
	mpz_t p_upper;
	mpz_init(p_upper);
	mpz_ui_pow_ui(p_upper, 2, ETA);
	// p_range = p_upper - p_lower
	mpz_t p_range;
	mpz_sub(temp, p_upper, p_lower);
	mpz_init_set(p_range, temp);
	// p odd and in [2^(eta - 1), 2^(eta))
	mpz_init2(p, ETA);
	mpz_urandomm(p, *randstate, p_range);
	mpz_mul_ui(p, p, 2);				// p *= 2
	mpz_add_ui(p, p, 1);				// p += 1 --> p odd
	mpz_mod(p, p, p_range);				// p %= prange
	
	// cleanup
	mpz_clear(temp);
	mpz_clear(p_lower);
	mpz_clear(p_upper);
	mpz_clear(p_range);
}

// Helper for keyGen
void genQ(mpz_t q[], mpz_t p, gmp_randstate_t* randstate)
{
	unsigned int i;
	unsigned int q_max = 0;
	// q_range = 2^GAMMA / p
	mpz_t q_range;
	mpz_init(q_range);
	// temp container
	mpz_t temp;
	mpz_init(temp);
	
	for (i=0; i<TAU; i++) { mpz_init(q[i]); }
	
	// q in [0, 2^GAMMA/p)
	mpz_ui_pow_ui(temp, 2, GAMMA);		// temp = 2^GAMMA
	mpz_fdiv_q(q_range, temp, p);		// q_range = temp/p
	mpz_sub_ui(q_range, q_range, 1);	// q_range-1, since we sometimes add one later (kludge)
	for (i=0; i<GAMMA; i++) {
		mpz_urandomm(q[i], *randstate, q_range);
		// save index of largest random, since that is required at index 0
		if (mpz_cmp(q[q_max], q[i]) < 0) {
			q_max = i;
		}
	}
	// relabel so that q[0] is odd and has largest value
	if (q_max != 0) {
		mpz_swap(q[0], q[q_max]);
	}
	if (mpz_even_p(q[0])) {
		mpz_add_ui(q[0], q[0], 1);	// make it odd
	}
	
	// cleanup
	mpz_clear(q_range);
}

void genR(mpz_t r[])
{
	
}