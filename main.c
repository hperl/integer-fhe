

#include <stdlib.h>
#include <stdio.h>

#include "test.h"

int main(int argc, char **argv)
{
	// test_encryt_decrypt();
	
	fhe_pk_t pk; fhe_sk_t sk;
	fhe_pk_init(pk); fhe_sk_init(sk);
	fhe_keygen(pk, sk);
	
	fhe_pk_print(pk);
	
	exit(0);
}



