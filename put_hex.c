#include "libft/libft.h"
#include "printf.h"
#include <stdarg.h>
void hex(long quotient)
{
   char hexadecimalnum[100];
   long remainder;
   int j = 0;
   int i = 0;
    while (quotient != 0)
    {
        remainder = quotient % 16;
        if (remainder < 10)
            hexadecimalnum[j++] = 48 + remainder;
        else
            hexadecimalnum[j++] = 55 + remainder;
        quotient = quotient / 16;
    }
	i = j-1;
	while(i>=0)
	{
		ft_putchar_fd(hexadecimalnum[i],1);
		i--;
	}
}

void hex_min(long quotient)
{
   char hexadecimalnum[100];
   long remainder;
   int j = 0;
   int i = 0;
    while (quotient != 0)
    {
        remainder = quotient % 16;
        if (remainder < 10)
            hexadecimalnum[j++] = 48 + remainder;
        else
            hexadecimalnum[j++] = 87 + remainder;
        quotient = quotient / 16;
    }
	i = j-1;
	while(i>=0)
	{
		ft_putchar_fd(hexadecimalnum[i],1);
		i--;
	}
}