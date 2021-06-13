#include "libft/libft.h"
#include "ft_printf.h"
#include <stdarg.h>



t_params get_params(const char *p,t_params params,t_flag flag,va_list *argptr)
{
	int t;

	char *len;
	int count,count1;
	int i ;
	count = 0;
	count1 = 0;
	if(flag.left==1)
		count++;
	if(flag.left_handle == 0 && (flag.left == 1 || flag.right == 1))
	{
		while(ft_isdigit(p[count]))
			count++;
		len = ft_substr(p,0,count);
		i = ft_atoi(len);
		params.before_dot = i;
		free(len);
	}
	else if(flag.left_handle == 1)
	{
		t =va_arg(*argptr,int);

		params.before_dot= t;
		while (!(ft_isdigit(p[count]) || is_conv(p[count])))
			count++;
		count--;
	}
	count1 = count;
	if(flag.right_handle == 1)
	{
		params.after_dot= va_arg(*argptr,int);
	}
	if(flag.pres == 1 && flag.pres_num == 1)
	{
		count1++;
		while(ft_isdigit(p[count1]))
			count1++;
		len = ft_substr(p,count+1,count1-1);
		i = ft_atoi(len);
		params.after_dot = i;
		free(len);
	}
	return(params);
}

void handle_int(const char *p,int t,t_flag flag,size_t length,t_params params)
{
	char *out = ft_itoa(t);
	char **tmp;
	int count = 0;
	int width = ft_strlen(out);
	int zeros = 0;
	int spaces = 0;
	int minus = 0;
	if(t < 0)
	{
		minus = 1;
		t *= -1;
		free(out);
		out  = ft_itoa(t); 
	}
	zeros = params.after_dot - width;
	if(zeros >0)
		spaces = params.before_dot - zeros - width;
	else
		spaces = params.before_dot - width;
	if(flag.left == 1 && flag.pres == 0)
	{
		write(1,out,width);
		while(params.before_dot-- -width)
		{
			ft_putchar_fd(' ',1);
		}
	}
	if(flag.left == 1 && flag.pres == 1 && minus == 0)
	{
		while (zeros > 0)
		{
			ft_putchar_fd('0',1);
			zeros--;
		}
		write(1,out,ft_strlen(out));
		while (spaces > 0)
		{
			ft_putchar_fd(' ',1);
			spaces--;
		}
	}
	if(flag.left == 1 && flag.pres == 1 && minus == 1)
	{
		spaces--;
		zeros++;
		ft_putchar_fd('-',1);
		while (zeros > 0)
		{
			ft_putchar_fd('0',1);
			zeros--;
		}
		write(1,out,ft_strlen(out));
		while (spaces > 0)
		{
			ft_putchar_fd(' ',1);
			spaces--;
		}
	}
	if(flag.right == 1 && flag.pres == 0)
	{
		while(params.before_dot-- -width > 0)
		{
			ft_putchar_fd(' ',1);
		}
		write(1,out,ft_strlen(out));
	}
	if(flag.right == 1 && flag.pres == 1 && minus == 0)
	{
		while (spaces > 0)
		{
			ft_putchar_fd(' ',1);
			spaces--;
		}
		while (zeros > 0)
		{
			ft_putchar_fd('0',1);
			zeros--;
		}
		write(1,out,ft_strlen(out));
	}
	if(flag.right == 1 && flag.pres == 1 && minus == 1)
	{
		spaces--;
		zeros++;
		while (spaces > 0)
		{
			ft_putchar_fd(' ',1);
			spaces--;
		}
		ft_putchar_fd('-',1);
		while (zeros > 0)
		{
			ft_putchar_fd('0',1);
			zeros--;
		}
		write(1,out,ft_strlen(out));
	}
}

int print_char(char c, t_flag flag,t_params params)
{
	int words;
	int count = 0;
	words = 0;
	if(flag.left == 1 )
	{
		ft_putchar_fd(c,1);
		params.before_dot  = params.before_dot *-1;
		while(params.before_dot-- -1)
		{
			ft_putchar_fd(' ',1);
		}
	}
	if(flag.right == 1)
	{
		while (params.before_dot--  -1 > 0)
		{
			ft_putchar_fd(' ',1);
		}
		ft_putchar_fd(c,1);
	}
	return(1);
}

int conv_length(const char *p,va_list *argptr,int t,t_flag flag)
{
	t_params params;

	params = get_params(p,params,flag,argptr);
	flag = check_star_left(flag,&params);
	int i = 0;
	char *out;
	while(!(is_conv(p[i])))
		i++;
	if(p[i] == 'd')
	{
			handle_int(p,va_arg(*argptr,int),flag,ft_strlen(out),params);
	}
	if(p[i] == 's')
	{
		out = va_arg(*argptr,char *);
		return(ft_strlen(out));
	}
	if(p[i] == 'c')
	{
		print_char(va_arg(*argptr,int),flag,params);
		return(1);
	}
	if(p[i] == 'u')
	{
		out_u_length(va_arg(*argptr,long));
	}
	if(p[i] == 'X')
	{
		return(hex_length(va_arg(*argptr,long)));
	}
	if(p[i] == 'x' || p[i] == 'X')
	{
		return(hex_length(va_arg(*argptr,long)));
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
			conv_length(p,&argptr,t,flag);
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
	ft_printf("%10.11d\n",20);
	printf("%10.11d\n",20);
}
