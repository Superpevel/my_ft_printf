#include "libft/libft.h"
#include "ft_printf.h"
#include <stdarg.h>

int check_zero(int t,t_flag flag,t_params params)
{
	int words = 0;
	if(t == 0 && (flag.pres_num == 0 || params.after_dot == 0) && flag.pres == 1)
	{
		while (params.before_dot-- > 0)
		{
			ft_putchar_fd(' ',1);
			words++;
		}
		return(words);
	}
	return(-1);
}

int handle_int(int t,t_flag flag,t_params params)
{
	int check = -1;
	check =check_zero(t ,flag,params);
	if(check>= 0)
		return(check);
	char *out = ft_itoa(t);
	int words = 0;
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
	if(zeros > 0)
		spaces = params.before_dot - zeros - width;
	else
		spaces = params.before_dot - width;
	if(flag.left == 1 && flag.pres == 0 && flag.zero == 0)
	{
		if(minus == 1)
		{
			ft_putchar_fd('-',1);
			words++;
		}
		write(1,out,ft_strlen(out));
		words+= (int)ft_strlen(out);
		while(params.before_dot-- -width > 0)
		{
			ft_putchar_fd(' ',1);
			words++;
		}
	}
	if(flag.left == 1 && flag.pres == 1 && minus == 0 && flag.zero == 0)
	{
		while (zeros > 0)
		{
			ft_putchar_fd('0',1);
			zeros--;
			words++;
		}
		write(1,out,ft_strlen(out));
		words+= (int)ft_strlen(out);
		while (spaces > 0)
		{
			ft_putchar_fd(' ',1);
			spaces--;
			words++;
		}
	}
	if(flag.left == 1 && flag.pres == 1 && minus == 1 && flag.zero == 0)
	{
		if(zeros>=0)
		{
			spaces--;
			zeros++;
		}
		words++;
		ft_putchar_fd('-',1);
		while (zeros > 0)
		{
			words++;
			ft_putchar_fd('0',1);
			zeros--;
		}
		write(1,out,ft_strlen(out));
		words+= (int)ft_strlen(out);
		while (spaces > 0)
		{
			words++;
			ft_putchar_fd(' ',1);
			spaces--;
		}
	}
	if(flag.right == 1 && flag.pres == 0 && flag.zero == 0)
	{
		while(params.before_dot-- -width > 0)
		{
			words++;
			ft_putchar_fd(' ',1);
		}
		write(1,out,ft_strlen(out));
		words+= (int)ft_strlen(out);
	}
	if(flag.right == 1 && flag.pres == 1 && minus == 0 && flag.zero == 0)
	{
		while (spaces > 0)
		{
			words++;
			ft_putchar_fd(' ',1);
			spaces--;
		}
		while (zeros > 0)
		{
			ft_putchar_fd('0',1);
			words++;
			zeros--;
		}
		write(1,out,ft_strlen(out));
		words+= (int)ft_strlen(out);
	}
	if(flag.right == 1 && flag.pres == 1 && minus == 1 && flag.zero==0)
	{
		if(zeros>=0)
		{
			spaces--;
			zeros++;
		}
		while (spaces > 0)
		{
			ft_putchar_fd(' ',1);
			words++;
			spaces--;
		}
		ft_putchar_fd('-',1);
		words++;
		while (zeros > 0)
		{
			ft_putchar_fd('0',1);
			words++;
			zeros--;
		}
		write(1,out,ft_strlen(out));
		words+= (int)ft_strlen(out);
	}
	if(flag.left == 0 && flag.right == 0 && flag.pres == 0 && flag.zero == 0) // mozno kiknut?
	{
		write(1,out,ft_strlen(out));
		words+= (int)ft_strlen(out);
	}

	if(flag.zero == 1)
	{
		if(minus == 0)
			zeros = params.before_dot - width;
		else
		{
			zeros = params.before_dot - width;
			ft_putchar_fd('-',1);
			words++;
		}
		while (zeros-- >0)
		{
			ft_putchar_fd('0',1);
			words++;
		}
		write(1,out,ft_strlen(out));
		words+= (int)ft_strlen(out);
	}
	free(out);
	return(words);
}
