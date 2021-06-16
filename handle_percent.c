#include "libft/libft.h"
#include "ft_printf.h"
int handle_per(t_flag flag,t_params params)
{
	int spaces = 0;
	int zeros = 0;
	int words = 1;
	if(flag.zero == 0)
		spaces = params.before_dot - 1;
	else
		zeros = params.before_dot - 1;
	if (flag.left == 1)
		ft_putchar_fd('%',1);
	while (spaces-- > 0)
	{
		ft_putchar_fd(' ',1);
		words++;
	}
	while (zeros-- > 0)
	{
		ft_putchar_fd('0',1);
		words++;
	}
	if (flag.right == 1)
		ft_putchar_fd('%',1);
	return(words);
}