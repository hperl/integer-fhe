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

#include "definitions.h"

/** private methods **/
void genSK(mpz_t p, gmp_randstate_t* randstate);
void genQ(mpz_t q[], mpz_t p, gmp_randstate_t* randstate);
void genR(mpz_t r[], gmp_randstate_t* randstate);
void genPK(mpz_t x[], mpz_t p, mpz_t q[], mpz_t r[], gmp_randstate_t* randstate);

extern int fhe_keygen(mpz_t pk[], mpz_t sk, int lambda);

#endif