/*
 *  types.c
 *  integer-fhe
 *
 *  Created by Henning Perl on 25.11.10.
 *  Copyright 2010 Henning Perl. All rights reserved.
 *
 */

#include "types.h"


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