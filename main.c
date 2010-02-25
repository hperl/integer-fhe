#define LAMBDA 4	// security parameter;		appropriate choice?
#define GAMMA 8		// bit-length of pk-ints;	appropriate choice?
#define ETA 64		// bit-length of sk;		= GAMMA^2
#define RHO 8		// bit-length of noise;		= GAMMA
#define TAU 12		// # ints in pk;			= LAMBDA + GAMMA

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <gmp.h>


void die(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

int keyGen(int lambda)
{
	// temp container
	mpz_t temp;
	mpz_init(temp);
	unsigned int i;
	
	// p_lower = 2^(ETA-1)
	mpz_t p_lower;
	mpz_init(p_lower);
	mpz_ui_pow_ui(p_lower, 2, ETA-1);
	// p_upper = 2^(ETA)
	mpz_t p_upper;
	mpz_init(p_upper);
	mpz_ui_pow_ui(p_upper, 2, ETA);
	// p_range = p_upper - p_lower
	mpz_t p_range;
	mpz_sub(temp, p_upper, p_lower);
	mpz_init_set(p_range, temp);
	// init random number generator
	gmp_randstate_t randstate;
	gmp_randinit_default(randstate);
	gmp_randseed_ui(randstate, time(NULL));
	
	// private key p
	mpz_t p;
	mpz_init2(p, ETA);
	// public key q
	mpz_t q[TAU];
	for (i=0; i<TAU; i++) { mpz_init(q[i]); }
	
	// p odd and in [2^(eta - 1), 2^(eta))
	mpz_urandomm(temp, randstate, p_range);
	mpz_urandomm(p, randstate, p_range);
	mpz_mul_ui(p, p, 2); // make odd
	mpz_add_ui(p, p, 1);
	mpz_mod(p, p, p_range);	// readjust to range
	
	gmp_printf("p = %Zd\n", p);
	return(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	keyGen(LAMBDA);
	exit(0);
}



