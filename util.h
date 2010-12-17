/*
 *  util.h
 *  integer-fhe
 *
 *  Created by Henning Perl on 27.11.10.
 *  Copyright 2010 Henning Perl. All rights reserved.
 *
 */

#pragma once

#include <gmp.h>
#include <libflint/fmpz_poly.h>
#include <libflint/F_mpz_mod_poly.h>

void fmpz_poly_to_F_mpz_mod_poly(F_mpz_mod_poly_t out, fmpz_poly_t in);

void fmpz_poly_rand_coeff_even(fmpz_poly_t poly, int n, ulong length, gmp_randstate_t* state);

int fmpz_probab_prime_p(fmpz_t n, int reps);