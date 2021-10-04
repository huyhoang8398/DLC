#include "gmp.h"
#include <stdio.h>
#include <time.h>

int main(int argc, char const *argv[])
{
	unsigned int k;
	mpz_t n;
	mpz_init(n);

	printf("Input K:");
	scanf("%u",&k);

	gmp_randstate_t rstate;
	gmp_randinit_default(rstate);

	long long int seed ;
	printf("Input seed:");
	scanf("%lld",&seed);
	gmp_randseed_ui(rstate,seed);
	gmp_printf("Seed in state: %Zd",rstate->_mp_seed);

	while (1) {
		mpz_urandomb(n,rstate,k);
		if ( mpz_probab_prime_p(n,20)==2 ) {
			gmp_printf("%Zd is prime \n",n);
			break;
		} else if (mpz_probab_prime_p(n,20)==1 ) {
			gmp_printf("%Zd is probably prime \n",n); 
		}
	}

	gmp_randclear(rstate);

	mpz_clear(n);
	return 0;
}
