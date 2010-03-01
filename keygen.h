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
#include <stdio.h>
#include <stdlib.h>

#include "definitions.h"

void genP(mpz_t p, gmp_randstate_t* randstate);
void genQ(mpz_t q[], mpz_t p, gmp_randstate_t* randstate);
int keyGen(int lambda);
void genR(mpz_t r[]);

extern int keyGen(int lambda);

#endif