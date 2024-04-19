#include <stdio.h>
#include "color.h"
void redcolor()
{
	printf("\x1b[31m");
}

void resetcolor()
{
	printf("\x1b[m");
}

void greencolor()
{
	printf("\x1b[32m");
}

void yellowcolor()
{
	printf("\x1b[33m");
}
