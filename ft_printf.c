#include "libft/libft.h"
#include "printf.h"
#include <stdarg.h>


typedef struct s_flags
{
	int pres;
	int zero;
	int left;
	int right;
}				t_flag;
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

void check_conv(const char *p,va_list argptr,t_flag flag,int t)
{
	char *out;
	if(*p == 'd')
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

int ft_printf(const char *p,...)
{
	va_list argptr;
	int t;
	t_flag flag;
	va_start (argptr, p);
	int i = 0;
	size_t count = 0;
	char *len;
	char *out;
	while(*p)
	{
		if(*p == '%')
		{
			if(*++p == '-')
			{
				p++;
				while(ft_isdigit(p[count]))
					count++;
				len = ft_substr(p,0,count);
				i = ft_atoi(len);
				out = malloc(sizeof(char) * 10);
				ft_memset(out,' ',i);
				while( )
			}
			else
			{
				check_conv(p,argptr,flag,t);
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
	ft_printf("%-105d final\n",2);
	// printf("%-10d finals\n",2);
}
