

#include <stdlib.h>
#include <stdio.h>

#include "test.h"

int main(int argc, char **argv)
{
	// test_encryt_decrypt();
	
	mpz_t c;
	mpz_init(c);
	int m;
	
	fhe_pk_t pk; fhe_sk_t sk;
	fhe_pk_init(pk); fhe_sk_init(sk);
	
	fhe_keygen(pk, sk);
	fhe_encrypt(c, pk, 1);
	fhe_recrypt(c, pk);
	m = fhe_decrypt(sk, c);
	printf("m = %i\n", m);
	
	exit(0);
}



