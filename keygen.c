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
#include <libflint/F_mpz_mod_poly.h>


#define N 8
#define MU 4
//#define NU 2**256;
#define LOG_NU 256

void die(char* str)
{
	exit(EXIT_FAILURE);
}

void fmpz_poly_to_F_mpz_mod_poly(F_mpz_mod_poly_t out, fmpz_poly_t in)
{
	mpz_poly_t mpz_poly;
	mpz_poly_init(mpz_poly);
	fmpz_poly_to_mpz_poly(mpz_poly, in);
	mpz_poly_to_F_mpz_mod_poly(out, mpz_poly);
	mpz_poly_clear(mpz_poly);
}

int fhe_keygen(fhe_pk_t pk, fhe_sk_t sk)
{
	mpz_t p;
	mpz_init(p);
	
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
		fmpz_clear(fmpz_p);
	} while (!mpz_probab_prime_p(p, 10));
	mpz_clear(rand_coeff);
		
//	gmp_printf("Choosing Prime p = %Zd\n", p);
//	printf("Choosing F(x) = ");
//	fmpz_poly_print_pretty(F, "x");
//	printf("\n");
//	printf("Choosing G(x) = ");
//	fmpz_poly_print_pretty(G, "x");
//	printf("\n");
	
	F_mpz_t P;
	F_mpz_init(P);
	F_mpz_set_mpz(P, p);
	
	F_mpz_mod_poly_t F_mod_p, G_mod_p, D_mod_p;
	F_mpz_mod_poly_init(F_mod_p, P);
	F_mpz_mod_poly_init(G_mod_p, P);
	F_mpz_mod_poly_init(D_mod_p, P);
	fmpz_poly_to_F_mpz_mod_poly(F_mod_p, F);
	fmpz_poly_to_F_mpz_mod_poly(G_mod_p, G);
	
	F_mpz_mod_poly_gcd_euclidean(D_mod_p, F_mod_p, G_mod_p);
	
	F_mpz_t *root = (F_mpz_t *)D_mod_p->coeffs;
	F_mpz_neg(*root, *root);	// root of D = -coeff[0]
	
	fmpz_t r = fmpz_init(fmpz_poly_resultant_bound(G, F)/FLINT_BITS + 2);
	fmpz_poly_scalar_div_mpz(G, G, p);
	fmpz_poly_scalar_div_mpz(F, F, p);
	fmpz_poly_t Z, T;
	fmpz_poly_init(Z);
	fmpz_poly_init(T);
	fmpz_poly_xgcd(r, Z, T, G, F);
	
	// build pk
	mpz_set(pk->p, p);
	F_mpz_get_mpz(pk->alpha, *root);
	// build sk
	mpz_set(sk->p, p);
	fmpz_poly_get_coeff_mpz(sk->B, Z, 0);
	mpz_mul_ui(p, p, 2);
	mpz_mod(sk->B, sk->B, p);

	mpz_clear(p);
	fmpz_poly_clear(T);
	fmpz_poly_clear(F);
	fmpz_poly_clear(G);
	F_mpz_mod_poly_clear(F_mod_p);
	F_mpz_mod_poly_clear(G_mod_p);
	F_mpz_mod_poly_clear(D_mod_p);
	F_mpz_clear(P);
	mpz_clear(NU_half);
	
	
	
	return(EXIT_SUCCESS);
}

/** memory management **/

void fhe_pk_init(fhe_pk_t pk)
{
	mpz_init(pk->p);
	mpz_init(pk->alpha);
	mpz_init(pk->s1);
	mpz_init(pk->s2);
	mpz_init(pk->SK);
	mpz_init(pk->H);
}


void fhe_pk_clear(fhe_pk_t pk)
{
	mpz_clear(pk->p);
	mpz_clear(pk->alpha);
	mpz_clear(pk->s1);
	mpz_clear(pk->s2);
	mpz_clear(pk->SK);
	mpz_clear(pk->H);
}


void fhe_sk_init(fhe_sk_t sk)
{
	mpz_init(sk->p);
	mpz_init(sk->B);
}


void fhe_sk_clear(fhe_sk_t sk)
{
	mpz_clear(sk->p);
	mpz_clear(sk->B);
}

/** output **/

void fhe_pk_print(fhe_pk_t pk)
{
	printf("public key:\n");
	gmp_printf("\tp  =\t%Zd\n", pk->p);
	gmp_printf("\tα  =\t%Zd\n", pk->alpha);
	gmp_printf("\ts1 =\t%Zd\n", pk->s1);
	gmp_printf("\ts2 =\t%Zd\n", pk->s2);
	gmp_printf("\tSK =\t%Zd\n", pk->SK);
	gmp_printf("\tH  =\t%Zd\n\n", pk->H);
}

void fhe_sk_print(fhe_sk_t sk)
{
	printf("secret key:\n");
	gmp_printf("\tp =\t%Zd\n", sk->p);
	gmp_printf("\tB =\t%Zd\n", sk->B);
}