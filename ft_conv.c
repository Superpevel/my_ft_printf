#include "ft_printf.h"

int	is_conv(char p)
{
	if (p == 'd' || p == 's' || p == 'c' || p == 'u'
		|| p == 'X' || p == 'x' || p == '%' || p == 'p' || p == 'i')
		return (1);
	return (0);
}

int	ft_write(int s, int words, int what)
{
	while (s-- > 0)
	{
		if (what == 1)
		{
			ft_putchar_fd(' ', 1);
			words++;
		}
		if (what == 2)
		{
			ft_putchar_fd('0', 1);
			words++;
		}
	}
	return (words);
}
