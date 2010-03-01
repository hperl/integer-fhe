

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
	
	//	for (i=0; i<TAU; i++) { gmp_printf("pk[%i] = %Zd\n", i, pk[i]);	}
	//	gmp_printf("sk = %Zd\n", sk);
	
	mpz_t c1;
	mpz_init(c1);
	mpz_t c2;
	mpz_init(c2);
	fhe_encrypt(c1, pk, 0);
	fhe_encrypt(c2, pk, 1);
	
	mpz_t sum;
	mpz_init(sum);
	fhe_add(sum, c1, c2, pk);
	
	int result;
	fhe_decrypt(result, sk, sum);
	printf("result: %i\n", result);
	
	fhe_decrypt(result, sk, c1);
	printf("test1: %i\n", result);
	fhe_decrypt(result, sk, c2);
	printf("test2: %i\n", result);

	
	exit(0);
}



