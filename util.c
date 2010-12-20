/*
 *  util.c
 *  integer-fhe
 *
 *  Created by Henning Perl on 27.11.10.
 *  Copyright 2010 Henning Perl. All rights reserved.
 *
 */

#include "util.h"

void
fmpz_poly_to_F_mpz_mod_poly(F_mpz_mod_poly_t out, fmpz_poly_t in)
{
	mpz_poly_t mpz_poly;
	mpz_poly_init(mpz_poly);
	fmpz_poly_to_mpz_poly(mpz_poly, in);
	mpz_poly_to_F_mpz_mod_poly(out, mpz_poly);
	mpz_poly_clear(mpz_poly);
}

void
fmpz_poly_rand_coeff_even(fmpz_poly_t poly, int n, ulong length, gmp_randstate_t* state)
{
	mpz_t c, exp_length_half;
	mpz_init(c);
	mpz_init(exp_length_half);
	
	mpz_ui_pow_ui(exp_length_half, 2, length-1);
	
	for (int i = 1; i<n; i++) {
		mpz_urandomb(c, *state, length);
		mpz_sub(c, c, exp_length_half);
		mpz_mul_ui(c, c, 2);
		fmpz_poly_set_coeff_mpz(poly, i, c);
	}
}

int
fmpz_probab_prime_p(fmpz_t n, int reps)
{
	int result;
	mpz_t mpz;
	
	mpz_init(mpz);
	fmpz_to_mpz(mpz, n);
	result = mpz_probab_prime_p(mpz, reps);
	mpz_clear(mpz);
	
	return result;
}
