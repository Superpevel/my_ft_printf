#include "ft_printf.h"

int	print_char2(char c, t_flag flag, int words)
{
	if (flag.right == 1)
	{
		while (flag.before_dot-- -1 > 0)
		{
			ft_putchar_fd(' ', 1);
			words++;
		}
		ft_putchar_fd(c, 1);
		words++;
		return (words);
	}
	return (0);
}

int	print_char(char c, t_flag flag)
{
	int	words;

	words = 0;
	if (flag.left == 1)
	{
		ft_putchar_fd(c, 1);
		words++;
		if (flag.before_dot < 0)
			flag.before_dot *= -1;
		while (flag.before_dot-- -1 > 0)
		{
			ft_putchar_fd(' ', 1);
			words++;
		}
	}
	words += print_char2(c, flag, words);
	return (words);
}
