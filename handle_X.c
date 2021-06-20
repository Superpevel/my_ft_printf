#include "ft_printf.h"

int	x_zero(t_flag flag, long num)
{
	int	spaces;
	int	words;

	words = 0;
	if (((flag.pres == 1 && flag.pres_num == 0)
			|| (flag.after_dot == 0 && flag.pres_num == 1)) && num == 0)
	{
		spaces = flag.before_dot;
		while (spaces--)
		{
			ft_putchar_fd(' ', 1);
			words++;
		}
		return (words);
	}
	return (-1);
}

void	check_flag_X(t_flag *flag, int len)
{
	if (flag->zero == 0)
	{
		flag->zeros = flag->after_dot - len;
		if (flag->zeros > 0)
			flag->spaces = flag->before_dot - flag->zeros - len;
		else
			flag->spaces = flag->before_dot - len;
	}
	if (flag->zero == 1)
	{
		flag->spaces = 0;
		flag->zeros = flag->before_dot - len;
		if (flag->after_dot == 0 && flag->pres_num == 1)
		{
			flag->spaces = flag->zeros;
			flag->zeros = 0;
		}
	}
}

int	printX(t_flag flag, int words, char *hexa, unsigned int num)
{
	if (flag.left == 1)
		words = ft_write(flag.zeros, words, 2);
	if (flag.left == 1)
	{
		if (num != 0)
			ft_putstr_fd(hexa, 1);
		else
			ft_putchar_fd('0', 1);
	}
	words = ft_write(flag.spaces, words, 1);
	if (flag.right == 1)
		words = ft_write(flag.zeros, words, 2);
	if (flag.right == 1)
	{
		if (num != 0)
			ft_putstr_fd(hexa, 1);
		else
			ft_putchar_fd('0', 1);
	}
	return (words);
}

int	handle_X(t_flag flag, unsigned int num)
{
	int		words;
	int		len;
	char	*hexa;

	words = 0;
	num = (unsigned int)(4294967295 + 1 + num);
	flag.zeros = x_zero(flag, num);
	if (flag.zeros >= 0)
		return (flag.zeros);
	hexa = ft_ull_base((unsigned long long)num, 16);
	len = ft_strlen(hexa);
	if (num != 0)
		words += len;
	else
	{
		len = 1;
		words += 1;
	}
	check_flag_X(&flag, len);
	words = printX(flag, words, hexa, num);
	free(hexa);
	return (words);
}
