

#include <stdlib.h>
#include <stdio.h>

#include "fhe_algorithm.h"

int main(int argc, char **argv)
{
	int i;
	mpz_t sk;
	mpz_init(sk);
	mpz_t pk[TAU];
	for (i=0; i<TAU; i++) { mpz_init(pk[i]); }
	
	fhe_keygen(pk, sk, LAMBDA);
	
	for (i=0; i<TAU; i++) { gmp_printf("pk[%i] = %Zd\n", i, pk[i]);	}
	gmp_printf("sk = %Zd\n", sk);
	
	mpz_t c0;
	mpz_init(c0);
	mpz_t c1;
	mpz_init(c1);
	fhe_encrypt(c0, pk, 0);
	fhe_encrypt(c1, pk, 1);
	
	mpz_t sum;
	mpz_init(sum);
	fhe_add(sum, c0, c1, pk);
	
	int result;
	fhe_decrypt(&result, sk, sum);
	printf("result (=1): %i\n", result);	// should be 0+1=1
	
	fhe_decrypt(&result, sk, c0);
	printf("test (=0): %i\n", result);		// should be c0=0
	fhe_decrypt(&result, sk, c1);
	printf("test (=1): %i\n", result);		// should be c1=1

	
	exit(0);
}



