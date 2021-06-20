#include "ft_printf.h"

int	check_zero(int t, t_flag flag)
{
	int		words;
	char	*out;

	words = 0;
	out = ft_itoa(t);
	if (t == 0 && (flag.pres_num == 0 || flag.after_dot == 0) && flag.pres == 1)
	{
		if (flag.left == 1 && flag.after_dot < 0)
		{
			write(1, out, ft_strlen(out));
			words += ft_strlen(out);
		}
		if (flag.after_dot < 0 )
			flag.before_dot = flag.before_dot - ft_strlen(out);
		words = ft_write(flag.before_dot, words, 1);
		if (flag.right == 1 && flag.after_dot < 0)
		{
			write(1, out, ft_strlen(out));
			words += ft_strlen(out);
		}
		free(out);
		return (words);
	}
	free(out);
	return (-1);
}

int	pls_work(t_flag flag, char *out)
{
	int	words;

	words = 0;
	if (flag.left == 1 && flag.pres == 1
		&& flag.int_minus == 1 && flag.zero == 0)
	{
		if (flag.zeros >= 0)
		{
			flag.spaces--;
			flag.zeros++;
		}
		words++;
		ft_putchar_fd('-', 1);
		while (flag.zeros-- > 0)
		{
			words++;
			ft_putchar_fd('0', 1);
		}
		write(1, out, ft_strlen(out));
		words += (int)ft_strlen(out);
		words = ft_write(flag.spaces, words, 1);
	}
	return (words);
}

int	words1(t_flag flag, int width, char *out)
{
	int	words;

	words = 0;
	if (flag.left == 1 && flag.pres == 0 && flag.zero == 0)
	{
		if (flag.int_minus == 1)
		{
			ft_putchar_fd('-', 1);
			words++;
		}
		write(1, out, ft_strlen(out));
		words += (int)ft_strlen(out);
		while (flag.before_dot-- -width > 0)
		{
			ft_putchar_fd(' ', 1);
			words++;
		}
	}
	return (words);
}
