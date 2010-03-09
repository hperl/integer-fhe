/*
 *  encrypt.c
 *  integer-fhe
 *
 *  Created by Henning Perl on 01.03.10.
 *
 */

#include "crypt.h"

void fhe_encrypt(mpz_t c, mpz_t pk[], int m)
{
	mpz_t r;
	mpz_init(r);
	int i;
	
	// init random number generator
	gmp_randstate_t randstate;
	gmp_randinit_default(randstate);
	gmp_randseed_ui(randstate, time(NULL));
	
	// range = 2^RHO
	mpz_t range;
	mpz_init(range);
	mpz_ui_pow_ui(range, 2, RHO);
	
	mpz_urandomm(r, randstate, range);
	mpz_mul_ui(r, r, 2);
	// we also want negative numbers ...
	if (gmp_urandomm_ui(randstate, 1) == 0) { // random in [0,1]
		mpz_neg(r, r);
	}
	
	mpz_add_ui(c, r, m);
	for (i=0; i<TAU; i++) {
		if (gmp_urandomm_ui(randstate, 1) == 0) { // random in [0,1]
			mpz_add(c, c, pk[i]);
		}
	}
}

void fhe_decrypt(int* m, mpz_t sk, mpz_t c)
{
	mpz_mod(c, c, sk);
	*m = (mpz_get_si(c) % 2);
}