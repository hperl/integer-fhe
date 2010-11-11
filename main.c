

#include <stdlib.h>
#include <stdio.h>

#include "fhe_algorithm.h"

int main(int argc, char **argv)
{
	fhe_pk_t pk;
	fhe_sk_t sk;
	
	fhe_keygen(pk, sk);
	
	exit(0);
}



