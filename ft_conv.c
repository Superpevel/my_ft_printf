#include "libft/libft.h"
#include "ft_printf.h"


int is_conv(char p)
{
	if(p == 'd' || p == 's' || p == 'c' || p == 'u' || p == 'X' || p == 'x')
		return(1);
	return(0);
}

void check_conv(const char *p,va_list argptr,int t)
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