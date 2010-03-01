/*
 *  evaluate.h
 *  integer-fhe
 *
 *  Created by Henning Perl on 01.03.10.
 *
 */

#ifndef EVALUATE_H_
#define EVALUATE_H_

#include <time.h>
#include <gmp.h>
#include <stdlib.h>

#include "definitions.h"

extern void fhe_add(mpz_t sum,  mpz_t add1, mpz_t add2, mpz_t pk[]);
extern void fhe_mul(mpz_t prod, mpz_t mul1, mpz_t mul2, mpz_t pk[]);

#endif