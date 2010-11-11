/*
 *  encrypt.h
 *  integer-fhe
 *
 *  Created by Henning Perl on 01.03.10.
 *
 */

#ifndef CRYPT_H_
#define CRYPT_H_

#include <time.h>
#include <gmp.h>
#include <stdlib.h>

extern void fhe_encrypt(mpz_t c, mpz_t pk[], int m);
extern void fhe_decrypt(int* m, mpz_t sk, mpz_t c);

#endif