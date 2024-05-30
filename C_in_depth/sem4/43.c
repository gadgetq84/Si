#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>
#define SIZE 1000
void zFunction2 (char *s, int z[]) {
int n = strlen(s);
for (int i=1, l=0, r=0; i<n; ++i) {
if (i <= r)
	z[i] = fmin((r-i+1), (z[i-l]));
while (i+z[i] < n && s[z[i]] == s[i+z[i]])
	++z[i];
if (i+z[i]-1 > r)
	l = i, r = i+z[i]-1;
}
}
//don't_panic
//nick_is_a_mastodon
int main()
{
char t[SIZE] = {0}, p[SIZE] = {0};
char s[SIZE+SIZE] = {0};
int z[SIZE+SIZE] = {0};

printf("Input text: ");
scanf("%s",t);
printf("Input word: ");
scanf("%s",p);
size_t tlen = strlen(t);
size_t plen = strlen(p);
sprintf(s,"%s#%s",p,t);
zFunction2(s,z);

for(size_t i=0; i<tlen; i++)
if((z[plen+i]+i-1)==tlen)
{
 printf("find result %u \n",z[plen+i]);
}
printf("\n");

return 0;
}
