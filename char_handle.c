#include "libft/libft.h"
#include "ft_printf.h"
#include <stdarg.h>

int print_char(char c, t_flag flag,t_params params)
{
	int words;
	words = 0;
	if(flag.left == 1)
	{
		ft_putchar_fd(c,1);
		words++;
		if(params.before_dot < 0)
			params.before_dot  = params.before_dot *-1;
		while(params.before_dot-- -1 > 0)
		{
			ft_putchar_fd(' ',1);
			words++;
		}
	}
	if(flag.right == 1)
	{
		while (params.before_dot--  -1 > 0)
		{
			ft_putchar_fd(' ',1);
			words++;
		}
		ft_putchar_fd(c,1);
		words++;
	}
	return(words);
}