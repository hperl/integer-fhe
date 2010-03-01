/*
 *  evaluate.c
 *  integer-fhe
 *
 *  Created by Henning Perl on 01.03.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "evaluate.h"

void fhe_add(mpz_t sum, mpz_t add1, mpz_t add2, mpz_t pk[])
{
	mpz_add(sum, add1, add2);
}

void fhe_mul(mpz_t prod, mpz_t mul1, mpz_t mul2, mpz_t pk[])
{
	mpz_add(prod, mul1, mul2);
}
