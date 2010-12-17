/*
 *  keygen.c
 *  integer-fhe
 *
 *  Created by Henning Perl on 01.03.10.
 *
 */

#include "integer-fhe.h"
#undef DEBUG

void
fhe_keygen(fhe_pk_t pk, fhe_sk_t sk)
{
	mpz_t p;
	mpz_init(p);
	fmpz_t fmpz_p;
	
	fmpz_poly_t F;
	fmpz_poly_init(F);
	// set f = x^n + 1
	fmpz_poly_set_coeff_ui(F, N, 1);
	fmpz_poly_set_coeff_ui(F, 0, 1);
	
	fmpz_poly_t G;
	fmpz_poly_init(G);
	
	gmp_randstate_t randstate;
	gmp_randinit_default(randstate);
	gmp_randseed_ui(randstate, time(0)); // make it deterministic for now
	do {
		fmpz_poly_rand_coeff_even(G, N, LOG_NU, &randstate);
		fmpz_t G_0 = fmpz_poly_get_coeff_ptr(G, 0);
		fmpz_add_ui(G_0, G_0, 1);
		// set p = resultant(G(x), F(x))
		fmpz_p = fmpz_init(fmpz_poly_resultant_bound(G, F)/FLINT_BITS + 2);
		fmpz_poly_resultant(fmpz_p, G, F);
		fmpz_to_mpz(p, fmpz_p);
		fmpz_clear(fmpz_p);
	} while (!mpz_probab_prime_p(p, 10));

#ifdef DEBUG
	gmp_printf("Choosing Prime p = %Zd\n", p);
	printf("Choosing F(x) = ");
	fmpz_poly_print_pretty(F, "x");
	printf("\n");
	printf("Choosing G(x) = ");
	fmpz_poly_print_pretty(G, "x");
	printf("\n");
#endif
	
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
	
#ifdef DEBUG
	printf("gcd(G(x), F(x) = ");
	F_mpz_mod_poly_print_pretty(D_mod_p, "x");
	printf("\n");
#endif
	
	F_mpz_t *root = (F_mpz_t *)D_mod_p->coeffs;
	F_mpz_neg(*root, *root);	// root of D = -coeff[0]
	F_mpz_mod(*root, *root, P);
	
	fmpz_t r = fmpz_init(fmpz_poly_resultant_bound(G, F)/FLINT_BITS + 2);

	fmpz_poly_t Z, T;
	fmpz_poly_init(Z);
	fmpz_poly_init(T);
	
#ifdef DEBUG
	printf("Executing XGCD with Polynomials G = ");
	fmpz_poly_print_pretty(G, "x");
	printf("\n and F = ");
	fmpz_poly_print_pretty(F, "x");
	printf("\n");
#endif
	fmpz_poly_xgcd(r, Z, T, G, F);
	
#ifdef DEBUG
	printf("r    = ");
	fmpz_print(r);
	printf("\n");
	printf("Z(x) = ");
	fmpz_poly_print_pretty(Z, "x");
	printf("\n");
#endif
	fmpz_p = fmpz_init(mpz_size(p));
	mpz_to_fmpz(fmpz_p, p);
	assert(fmpz_equal(fmpz_p, r));
	
	// build pk
	mpz_set(pk->p, p);
	F_mpz_get_mpz(pk->alpha, *root);
	// build sk
	mpz_set(sk->p, p);
	fmpz_poly_get_coeff_mpz(sk->B, Z, 0);
	mpz_mul_ui(p, p, 2);
	mpz_mod(sk->B, sk->B, p);

	mpz_clear(p);
	fmpz_clear(fmpz_p);
	fmpz_poly_clear(T);
	fmpz_poly_clear(F);
	fmpz_poly_clear(G);
	F_mpz_mod_poly_clear(F_mod_p);
	F_mpz_mod_poly_clear(G_mod_p);
	F_mpz_mod_poly_clear(D_mod_p);
	F_mpz_clear(P);
}

void
fhe_encrypt(mpz_t c, fhe_pk_t pk, int m)
{
#ifdef DEBUG
	printf("ENCRYPT %i\n", m);
#endif
	if ((m != 0) && (m != 1)) {
		fprintf(stderr, "\nm must be either 0 or 1\n");
		abort();
	}
	
	fmpz_poly_t C;
	fmpz_t C_0, fmpz_c, alpha;
	
	fmpz_poly_init(C);
	fmpz_c = fmpz_init(14351);
		
	alpha = fmpz_init(mpz_size(pk->alpha));
	mpz_to_fmpz(alpha, pk->alpha);
	
	gmp_randstate_t randstate;
	gmp_randinit_default(randstate);
	gmp_randseed_ui(randstate, time(0));
	
	fmpz_poly_rand_coeff_even(C, N, 2, &randstate);
	
	C_0 = fmpz_poly_get_coeff_ptr(C, 0);
	fmpz_add_ui(C_0, C_0, m);
	
	fmpz_poly_evaluate(fmpz_c, C, alpha);
	
#ifdef DEBUG
	printf("C(x) = ");
	fmpz_poly_print_pretty(C, "x");
	printf("\n");
	printf("C(alpha) = ");
	fmpz_print(fmpz_c);
	printf("\n");
#endif
	
	fmpz_to_mpz(c, fmpz_c);
	mpz_mod(c, c, pk->p);
	
	
#ifdef DEBUG
	gmp_printf("c = %Zd\n", c);
#endif
	
	// cleanup
	fmpz_poly_clear(C);
	fmpz_clear(fmpz_c);
	fmpz_clear(alpha);
}

int
fhe_decrypt(fhe_sk_t sk, mpz_t c)
{
#ifdef DEBUG
	gmp_printf("DECRYPT %Zd\n", c);
#endif
	int m;
	
	mpz_t temp, q, r;
	mpz_init(temp);
	mpz_init(q);
	mpz_init(r);
	
	mpq_t n, d, one_half;
	mpq_init(n);
	mpq_init(d);
	mpq_init(one_half);
	
	mpz_mul(temp, c, sk->B);
	mpz_fdiv_qr(q, r, temp, sk->p);
	
	// round: add 1 to q if r/p > 1/2
	mpq_set_ui(one_half, 1, 2);
	mpq_set_z(n, r);
	mpq_set_z(d, sk->p);
	mpq_div(n, n, d);
	
	if (mpq_cmp(n, one_half) > 0) { // n > 1/2
		mpz_add_ui(q, q, 1);
	}
	
#ifdef DEBUG
	gmp_printf("q: %Zd\n", q);
#endif
	
	mpz_add(temp, c, q);	
	mpz_mod_ui(temp, temp, 2);
	
	m = mpz_get_si(temp);
		
	// cleanup
	mpz_clear(temp);
	mpz_clear(q);
	mpz_clear(r);
	mpq_clear(n);
	mpq_clear(d);
	mpq_clear(one_half);
	
	return m;
}

void
fhe_add(mpz_t res, mpz_t a, mpz_t b, fhe_pk_t pk)
{
	mpz_add(res, a, b);
	mpz_mod(res, res, pk->p);
}

void
fhe_mult(mpz_t res, mpz_t a, mpz_t b, fhe_pk_t pk)
{
	mpz_mul(res, a, b);
	mpz_mod(res, res, pk->p);
}
