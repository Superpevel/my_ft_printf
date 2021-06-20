#include "ft_printf.h"

int	right(t_flag flag, char *out, unsigned int num)
{
	if (flag.left == 1)
	{
		if (num != 0)
			ft_putstr_fd(out, 1);
		else
			ft_putchar_fd('0', 1);
	}
	return (0);
}

void	right_out(t_flag flag, char *out, unsigned int num)
{
	if (flag.right == 1)
	{
		if (num != 0)
			ft_putstr_fd(out, 1);
		else
			ft_putchar_fd('0', 1);
	}
}

void	flag_params(int len, t_flag *flag)
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

int	words_count(char *out, int len, unsigned int num, t_flag flag)
{
	int	words;

	words = 0;
	if (num != 0)
		words += len;
	else
	{
		len = 1;
		words += 1;
	}
	flag_params(len, &flag);
	if (flag.left == 1)
		words = ft_write(flag.zeros, words, 2);
	words += right(flag, out, num);
	words = ft_write(flag.spaces, words, 1);
	if (flag.right == 1)
		words = ft_write(flag.zeros, words, 2);
	right_out(flag, out, num);
	return (words);
}

int	u_handle(t_flag flag, unsigned int num)
{
	int		words;
	int		zeros;
	char	*out;
	int		len;

	num = (unsigned int)(4294967295 + 1 + num);
	zeros = x_zero(flag, num);
	if (zeros >= 0)
		return (zeros);
	out = ft_u_itoa(num);
	len = ft_strlen(out);
	words = words_count(out, len, num, flag);
	free(out);
	return (words);
}
