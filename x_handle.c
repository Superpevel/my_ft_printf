#include "libft/libft.h"
#include "ft_printf.h"

int x_handle(t_flag flag,t_params params,long num)
{
	int spaces;
	int words = 0;
	int zeros;
	int len = hex_length(num);

	zeros = x_zero(flag,params,num);
	if(zeros >= 0)
		return(zeros);
	else
		zeros =0;
	if(num != 0)
		words+=len;
	else
	{
		len = 1;
		words+=1;
	}
	if(flag.zero == 0)
	{
		zeros = params.after_dot - len;
		if(zeros>0)
			spaces = params.before_dot - zeros - len;
		else
			spaces = params.before_dot - len;
	}
	if(flag.zero == 1)
	{
		spaces = 0;
		zeros = params.before_dot - len;
	}
	if(flag.left == 1)
		while (zeros-- > 0)
		{
			ft_putchar_fd('0',1);
			words++;
		}
	if(flag.left == 1)
	{
		if(num != 0)
			hex_min(num);
		else
			ft_putchar_fd('0',1);
	}
	while (spaces-- > 0)
	{
		ft_putchar_fd(' ',1);
		words++;
	}
	if(flag.right == 1)
		while (zeros-- >0)
		{
			ft_putchar_fd('0',1);
			words++;
		}
	if(flag.right == 1)
	{
		if(num != 0)
			hex_min(num);
		else
			ft_putchar_fd('0',1);
	}
	return(words);
}