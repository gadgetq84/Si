
#include <stdio.h>
#define N 1000

int cnk(int n,int k)
{
	int c[N] = {0};
	int i, j;
	c[0] = 1;
	for (j = 1; j <= n; j++)
		for (i = j; i >= 1; i--)
			c[i] = c[i - 1] + c[i];
	return c[k];
}
int main(void)
{
	int n,k;
	printf("enter two integers N space M:");
	scanf ("%d%d", &n,&k);
	printf("%d",cnk(n,k));
return 0;
}
