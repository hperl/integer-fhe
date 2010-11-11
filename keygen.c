/*
 *  keygen.c
 *  integer-fhe
 *
 *  Created by Henning Perl on 01.03.10.
 *
 */

#include "keygen.h"
#include <time.h>
#include <stdio.h>
#include <libflint/flint.h>
#include <libflint/fmpz_poly.h>
#include <libflint/zmod_poly.h>


#define N 8
#define MU 4
//#define NU 2**256;
#define LOG_NU 256

void die(char* str)
{
	exit(EXIT_FAILURE);
}

int fhe_keygen(fhe_pk_t pk, fhe_sk_t sk)
{
	mpz_t p;
	mpz_init(p);
	unsigned long p_ui;
	
	mpz_t NU_half;
	mpz_init(NU_half);
	mpz_ui_pow_ui(NU_half, 2, LOG_NU-1);
	
	fmpz_poly_t F;
	fmpz_poly_init(F);
	// set f = x^n + 1
	fmpz_poly_set_coeff_ui(F, N, 1);
	fmpz_poly_set_coeff_ui(F, 0, 1);
	
	fmpz_poly_t G;
	fmpz_poly_init(G);
	
	mpz_t rand_coeff;
	mpz_init(rand_coeff);
	gmp_randstate_t randstate;
	gmp_randinit_default(randstate);
//	gmp_randseed_ui(randstate, time(0)); // make it deterministic for now
	do {
		// create G(x)
		mpz_urandomb(rand_coeff, randstate, LOG_NU);
		mpz_sub(rand_coeff, rand_coeff, NU_half);
		mpz_mul_ui(rand_coeff, rand_coeff, 2);
		mpz_add_ui(rand_coeff, rand_coeff, 1);
		fmpz_poly_set_coeff_mpz(G, 0, rand_coeff);
		for (int i = 1; i<N; i++) {
			mpz_urandomb(rand_coeff, randstate, LOG_NU);
			mpz_sub(rand_coeff, rand_coeff, NU_half);
			// G(x) = 1 + 2 S(x)
			mpz_mul_ui(rand_coeff, rand_coeff, 2);
			fmpz_poly_set_coeff_mpz(G, i, rand_coeff);
		}
		// set p = resultant(G(x), F(x))
		fmpz_t fmpz_p = fmpz_init(fmpz_poly_resultant_bound(G, F)/FLINT_BITS + 2);
		fmpz_poly_resultant(fmpz_p, G, F);
		fmpz_to_mpz(p, fmpz_p);
	} while (!mpz_probab_prime_p(p, 10));
	mpz_clear(rand_coeff);
	
	p_ui = mpz_get_ui(p);
	
	gmp_printf("Choosing Prime p = %Zd\n", p);
    printf("unsigned long p = %lu\n", p_ui);
	printf("Choosing F(x) = ");
	fmpz_poly_print_pretty(F, "x");
	printf("\n");
	printf("Choosing G(x) = ");
	fmpz_poly_print_pretty(G, "x");
	printf("\n");
	
	fmpz_poly_t D;
	fmpz_poly_init(D);
	fmpz_poly_gcd(D, F, G);
	
	fmpz_poly_gcd_modular(<#fmpz_poly_t H#>, <#const fmpz_poly_t poly1#>, <#const fmpz_poly_t poly2#>, <#const unsigned long bits1#>, <#const unsigned long bits2#>);
	
	printf("D(x) = ");
	fmpz_poly_print_pretty(D, "x");
	printf("\n");
	
	return(EXIT_SUCCESS);
}
