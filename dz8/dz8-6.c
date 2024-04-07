
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int sdiag(int size, int a[size][size])
{
    int sum = 0;
    for (int i = 0; i < size; i++)
        sum = sum + a[i][i];
    return sum;
}

void smass(int size, int a[size][size])
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            scanf("%d", &a[i][j]);
    }
}

int main()
{
    int size = 5;
    int a[size][size];
    smass(size, a);
    int average = (sdiag(size, a)) / size;
    int count_max = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (a[i][j] > average)
                count_max++;
        }
    }
    printf("%d", count_max);
    return 0;
}

