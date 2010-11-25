

#include <stdlib.h>
#include <stdio.h>

#include "fhe_algorithm.h"

int main(int argc, char **argv)
{
	fhe_pk_t pk;
	fhe_sk_t sk;
	fhe_pk_init(pk);
	fhe_sk_init(sk);
	
	fhe_keygen(pk, sk);
	fhe_pk_print(pk);
	fhe_sk_print(sk);
	
	fhe_pk_clear(pk);
	fhe_sk_clear(sk);
	exit(0);
}



