#include "libft/libft.h"
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
	i = j;
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
	i = j;
	while(i>=0)
	{
		ft_putchar_fd(hexadecimalnum[i],1);
		i--;
	}
}

void put(long i )
{
	if(i>=10)
	{
		put(i/10);
		ft_putchar_fd(i%10 + '0',1);
	}
	else if(i<10)
	{
		ft_putchar_fd(i%10 + '0',1);
	}
}

void out_u(long i)
{
	if(i<0)
	{
		put(4294967295 - i +1);
	}
	else
	{
		put(i);
	}
}

int ft_printf(const char *p,...)
{
	va_list argptr;
	int t;
	va_start (argptr, p);
	char *out;
	while(*p)
	{
		if(*p == '%')
		{
			if(*++p == 'd')
			{
				t = va_arg(argptr,int);
				out = ft_itoa(t);
				write(1,out,ft_strlen(out));
			}
			if(*p == 's')
			{
				out = va_arg(argptr,char *);
				write(1,out,ft_strlen(out));
			}
			if(*p == 'c')
			{
				ft_putchar_fd(va_arg(argptr,int ),1);
			}
			if(*p == 'u')
			{
				out_u(va_arg(argptr,long));
			}
			if(*p == 'X')
			{
				hex(va_arg(argptr,long));
			}
			if(*p == 'x')
			{
				hex_min(va_arg(argptr,long));
			}
		}
		else
		{
			write(1,p,1);
		}
		p++;
	}
	return(0);
}
int main()
{
	ft_printf("%x ",2147483647);
	printf("%.0x" ,2147483647);
}
