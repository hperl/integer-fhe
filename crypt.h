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

void fhe_encrypt(mpz_t c, fhe_pk_t pk, short m);
void fhe_decrypt(short m, fhe_sk_t sk, mpz_t c);

#endif