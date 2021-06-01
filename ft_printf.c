#include "libft/libft.h"
#include "printf.h"
#include <stdarg.h>


typedef struct s_flags
{
	int pres;
	int zero;
	int left;
	int right;
	int left_handle;
	int right_handle;
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

size_t check_conv(const char *p,va_list argptr,t_flag flag,int t)
{
	char *out;
	if(*p == 'd')
	{
			t = va_arg(argptr,int);
			out = ft_itoa(t);
			write(1,out,ft_strlen(out));
			return(ft_strlen(out));
	}
	if(*p == 's')
	{
		out = va_arg(argptr,char *);
		write(1,out,ft_strlen(out));
		return(ft_strlen(out));
	}
	if(*p == 'c')
	{
		ft_putchar_fd(va_arg(argptr,int ),1);
		return(1);
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
	return(0);
}


int is_conv(char p)
{
	if(p == 'd' || p == 's' || p == 'c' || p == 'u' || p == 'X' || p == 'x')
		return(1);
	return(0);
}

t_flag init_flag(t_flag flag)
{
	flag.pres = 0;
	flag.zero = 0;
	flag.left = 0;
	flag.right = 0;
	flag.left_handle = 0;
	flag.right_handle = 0;
	return(flag);
}
int flag_handler(t_flag flag,const char *p)
{
	int i;

	i = 0;
	while(!is_conv(p[i]))
	{
		if(p[i] == '*' && flag.pres == 0)
				flag.left_handle = 1;
		if(p[i] == '*' && flag.pres == 1)
				flag.right_handle = 1;
		if(p[i] == '-' && flag.pres == 0 && flag.left_handle == 0)
			flag.left = 1;
		if(flag.left_handle == 0 && flag.left == 0 && flag.pres == 0 && ft_isdigit(p[i]))
			flag.right = 1;
		if(p[i] == '.')
			flag.pres = 1;
		i++;
	}
	printf("flags left %d \n",flag.left);
	printf("flags left_handle %d \n",flag.left_handle);
	printf("flags right_handle %d \n",flag.right_handle);
	printf("flags right %d \n",flag.right);
	printf("flags pres %d \n",flag.pres);
	return(i);
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
			// if(*++p == '-')
			// {
			// 	p++;
			// 	while(ft_isdigit(p[count]))
			// 		count++;
			// 	len = ft_substr(p,0,count);
			// 	i = ft_atoi(len);
			// 	p = p+count;
			// 	count = check_conv(p,argptr,flag,t);
			// 	i = i-count;
			// 	if(i > 0)
			// 		while(i)
			// 		{
			// 			ft_putchar_fd(' ',1);
			// 			i--;
			// 		}
			// }
			// else
			// {
			// 	check_conv(p,argptr,flag,t);
			// }
			flag = init_flag(flag);
			flag_handler(flag,p++);
		}
		else
		{
			write(1,p,1);
		}
		p++;
	}
	return (0);
}
int main()
{
	ft_printf("%10d",20);
	printf("%-*.1dfinals\n",1,20);
}
