#include "ft_printf.h"

int	p_zero(t_flag flag, long num)
{
	int	words;

	words = 0;
	if (((flag.pres == 1 && flag.pres_num == 0)
			|| (flag.after_dot == 0 && flag.pres_num == 1)) && num == 0)
	{
		flag.spaces = flag.before_dot;
		while (flag.spaces--)
		{
			ft_putchar_fd(' ', 1);
			words++;
		}
		return (words);
	}
	return (-1);
}

int	words_out(unsigned long long num, int words, char *prefix, char *out)
{
	if (num != 0)
	{
		ft_putstr_fd(prefix, 1);
		ft_putstr_fd(out, 1);
	}
	else
	{
		ft_putstr_fd(prefix, 1);
		ft_putchar_fd('0', 1);
		words += 2;
	}
	return (words);
}

int	print_p(t_flag flag, int words, unsigned long long num, char *out)
{
	char	*prefix;

	prefix = "0x";
	if (flag.left == 1)
		words = ft_write(flag.zeros, words, 2);
	if (flag.left == 1)
		words = words_out(num, words, prefix, out);
	words = ft_write(flag.spaces, words, 1);
	if (flag.right == 1)
		words =ft_write(flag.zeros, words, 2);
	if (flag.right == 1)
		words = words_out(num, words, prefix, out);
	return (words);
}

int	handle_p(t_flag flag, unsigned long long num)
{
	int		words;
	char	*out;
	int		len;

	words = 0;
	out = to_lower_str(ft_ull_base(num, 16));
	len = ft_strlen(out) + 2;
	flag.zeros = p_zero(flag, num);
	if (flag.zeros >= 0)
		return (flag.zeros);
	else
		flag.zeros = 0;
	if (num != 0)
		words += len;
	else
	{
		len = 3;
		words += 1;
	}
	flag_params(len, &flag);
	words = print_p(flag, words, num, out);
	free(out);
	return (words);
}
