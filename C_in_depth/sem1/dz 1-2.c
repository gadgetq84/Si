#include <stdio.h>
#include <locale.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

int main(int argc, char **argv)
{
	setlocale( LC_ALL,"Rus" );
	long long unsigned int dig;
	uint32_t mask = 0xff000000;
	printf("enter the number :");
	scanf("%lld",&dig);
	uint32_t ret = mask^dig;
	printf("Result %u  \n",ret);
	return 0;
}

