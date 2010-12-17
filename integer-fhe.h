/*
 *  keygen.h
 *  integer-fhe
 *
 *  Created by Henning Perl on 01.03.10.
 *
 */

#pragma once

#include <gmp.h>
#include <assert.h>
#include <libflint/fmpz_poly.h>
#include <libflint/F_mpz_mod_poly.h>
#include "types.h"
#include "parameters.h"
#include "util.h"

/** main function **/

void fhe_keygen(fhe_pk_t pk, fhe_sk_t sk);

void fhe_encrypt(mpz_t c, fhe_pk_t pk, int m);

int  fhe_decrypt(fhe_sk_t sk, mpz_t c);

void fhe_add(mpz_t res, mpz_t a, mpz_t b, fhe_pk_t pk);

void fhe_mult(mpz_t res, mpz_t a, mpz_t b, fhe_pk_t pk);
