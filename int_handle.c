#include "ft_printf.h"

int	flag_zero_check(t_flag flag, int words, int width, char *out)
{
	if (flag.zero == 1)
	{
		flag.spaces = 0;
		if (flag.int_minus == 0)
			flag.zeros = flag.before_dot - width;
		else
		{
			flag.zeros = flag.before_dot - width;
			words++;
		}
		if (flag.after_dot == 0 && flag.pres_num == 1)
		{
			flag.zeros = 0;
			flag.spaces = flag.before_dot - width;
		}
		words = ft_write(flag.spaces, words, 1);
		if (flag.int_minus != 0)
			ft_putchar_fd('-', 1);
		words = ft_write(flag.zeros, words, 2);
		write(1, out, ft_strlen(out));
		words += (int)ft_strlen(out);
	}
	return (words);
}

void	flag_int_check(t_flag *flag, int width)
{
	flag->zeros = flag->after_dot - width;
	if (flag->zeros > 0)
		flag->spaces = flag->before_dot - flag->zeros - width;
	else
		flag->spaces = flag->before_dot - width;
	if (flag->space_flag == 1)
	{
		if (flag->spaces > 0)
			flag->spaces++;
		else
			flag->spaces = 1;
	}
}

int	check_flag_3(t_flag *flag, int width, int words, char *out)
{
	words += pls_work(*flag, out);
	if (flag->right == 1 && flag->pres == 0 && flag->zero == 0)
	{
		while (flag->before_dot-- -width > 0)
		{
			words++;
			ft_putchar_fd(' ', 1);
		}
		if (flag->int_minus == 1)
		{
			words++;
			ft_putchar_fd('-', 1);
		}
		write(1, out, ft_strlen(out));
		words += (int)ft_strlen(out);
	}
	if (flag->right == 1 && flag->pres == 1
		&& flag->int_minus == 0 && flag->zero == 0)
	{
		words = ft_write(flag->spaces, words, 1);
		words = ft_write(flag->zeros, words, 2);
		write(1, out, ft_strlen(out));
		words += (int)ft_strlen(out);
	}
	return (words);
}

int	check_flag_2(t_flag *flag, int words, int width, char *out)
{
	if (flag->left == 1 && flag->pres == 1
		&& flag->int_minus == 0 && flag->zero == 0)
	{
		words = ft_write(flag->zeros, words, 2);
		write(1, out, ft_strlen(out));
		words += (int)ft_strlen(out);
		words = ft_write(flag->spaces, words, 1);
	}
	words = check_flag_3(flag, width, words, out);
	if (flag->right == 1 && flag->pres == 1
		&& flag->int_minus == 1 && flag->zero == 0)
	{
		if (flag->zeros >= 0)
		{
			flag->spaces--;
			flag->zeros++;
		}
		words = ft_write(flag->spaces, words, 1);
		ft_putchar_fd('-', 1);
		words++;
		words = ft_write(flag->zeros, words, 2);
		write(1, out, ft_strlen(out));
		words += (int)ft_strlen(out);
	}
	return (flag_zero_check(*flag, words, width, out));
}

int	handle_int(int t, t_flag flag)
{
	char	*out;
	int		width;
	int		words;

	words = check_zero(t, flag);
	if (words >= 0)
		return (words);
	else
		words = 0;
	out = ft_itoa(t);
	width = ft_strlen(out);
	if (t < 0)
	{
		free(out);
		flag.int_minus = 1;
		if (t == -2147483648)
			out = ft_strdup("2147483648");
		else
			out = ft_itoa(t * -1);
	}
	flag_int_check(&flag, width);
	words += words1(flag, width, out);
	words = check_flag_2(&flag, words, width, out);
	free(out);
	return (words);
}
