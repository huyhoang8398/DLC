#include "gmp.h"
#include <stdio.h>
#include <time.h>

int main(int argc, char const *argv[])
{
	unsigned long k;
	printf("Input K:");
	scanf("%lu",&k);

	gmp_randstate_t rstate;
	gmp_randinit_default(rstate);
	long seed ;
	printf("Input seed:");
	scanf("%ld",&seed);
	gmp_randseed_ui(rstate,seed);

	mpz_t n1,n2,n3;
	mpz_inits(n1,n2,n3,NULL);

	mpz_rrandomb(n1,rstate,k);
	gmp_printf("%Zd is exactly %lu bits \n",n1,k);

	mpz_t zbase,zrange,zmaxrange;
	mpz_inits(zbase,zrange,zmaxrange,NULL);

	mpz_ui_pow_ui(zmaxrange,10,k);
	mpz_urandomm(n2,rstate,zmaxrange);
	gmp_printf("%Zd is at most %lu digits \n",n2,k);

	mpz_ui_pow_ui(zbase,10,k-1);
	mpz_mul_ui(zrange,zbase,9);
	mpz_urandomm(n3,rstate,zrange);
	mpz_add(n3,n3,zbase);
	gmp_printf("%Zd is exactly %lu digits \n",n3,k);

	mpz_clears(zbase,zrange,zmaxrange,NULL);

	gmp_randclear(rstate);

	mpz_clears(n1,n2,n3,NULL);
	return 0;
}
