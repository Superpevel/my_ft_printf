#include "libft/libft.h"
#include "ft_printf.h"
#include <stdarg.h>



int conv_length(const char *p,va_list argptr,int t,t_flag flag)
{
	t_params params;
	params = init_params(params);
	params = get_params(p,params,flag,argptr);
	flag = check_star_left(flag,params);

	int i = 0;
	char *out;
	while(!(is_conv(p[i])))
		i++;
	if(p[i] == 'd')
	{
			t = va_arg(argptr,int);
			if(t<0)
			{
				params.minus_number = 1;
				t *=-1;
			}
			out = ft_itoa(t);
			handle_int(p,out,flag,params);
			free(out);
	}
	if(p[i] == 's')
	{
		out = va_arg(argptr,char *);
		return(ft_strlen(out));
	}
	if(p[i] == 'c')
	{
		return(1);
	}
	if(p[i] == 'u')
	{
		out_u_length(va_arg(argptr,long));
	}
	if(p[i] == 'X')
	{
		return(hex_length(va_arg(argptr,long)));
	}
	if(p[i] == 'x' || p[i] == 'X')
	{
		return(hex_length(va_arg(argptr,long)));
	}
	return(0);
}

int until_conv(const char *p)
{
	int i;

	i = 0;
	while(!is_conv(p[i]))
		i++;
	return(i);
}

int flag_out_put(t_flag flag,const char *p,va_list argptr,int i)
{
	int t;
	if(flag.left == 0 && flag.left_handle == 0 && flag.pres == 0 && flag.pres_num == 0 && flag.right == 0 && flag.right_handle == 0)
	{
		check_conv(p,argptr,t);
	}
	else
	{
		conv_length(p,argptr,i,flag);
	}
	return(0);
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
	while(*p)
	{
		if(*p == '%')
		{
			flag = init_flag(flag);
			flag = flag_handler(flag,p++);
			conv_length(p,argptr,t,flag);
			i = until_conv(p);
			p = p+i;
		}
		else
			write(1,p,1);
		p++;
	}
	return (0);
}

int main()
{
	ft_printf("%5.3d %*d \n",-10,-20,-30);
	printf("%5.3d %*d \n",-10,-20,-30);
}
