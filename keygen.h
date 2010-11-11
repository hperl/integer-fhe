/*
 *  keygen.h
 *  integer-fhe
 *
 *  Created by Henning Perl on 01.03.10.
 *
 */

#ifndef KEYGEN_H_
#define KEYGEN_H_

#include <time.h>
#include <gmp.h>
#include <stdlib.h>

/** type defs **/
typedef struct {
	mpz_t p, alpha, s1, s2, SK, H;
} fhe_pk_t;

typedef struct {
	mpz_t p, b;
} fhe_sk_t;

extern int fhe_keygen(fhe_pk_t pk, fhe_sk_t sk);

/** private methods **/


#endif