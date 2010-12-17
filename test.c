/*
 *  test.c
 *  integer-fhe
 *
 *  Created by Henning Perl on 17.12.10.
 *
 */

#include "test.h"


void
test_encryt_decrypt()
{		
	for (int i = 0; i < RUNS; i++) {
		int m0, m1;
		mpz_t c0, c1;
		
		mpz_init(c0);
		mpz_init(c1);
		
		fhe_pk_t pk;
		fhe_sk_t sk;
		fhe_pk_init(pk);
		fhe_sk_init(sk);
		
		fhe_keygen(pk, sk);
		printf("\n");
		
		for (int j = 0; j < RUNS; j++) {
			fhe_encrypt(c0, pk, 0);
			m0 = fhe_decrypt(sk, c0);
			fhe_encrypt(c1, pk, 1);
			m1 = fhe_decrypt(sk, c1);
			
			assert(m0 == 0);
			assert(m1 == 1);
			printf(".");
		}
		
		fhe_pk_clear(pk);
		fhe_sk_clear(sk);
	}
	printf(" PASSED.\n");
	}