#include "ft_printf.h"

t_flag	init_flag(t_flag flag)
{
	flag.pres = 0;
	flag.zero = 0;
	flag.left = 0;
	flag.right = 0;
	flag.left_handle = 0;
	flag.right_handle = 0;
	flag.pres_num = 0;
	flag.space_flag = 0;
	flag.after_dot = 0;
	flag.before_dot = 0;
	flag.int_minus = 0;
	flag.spaces = 0;
	flag.zeros = 0;
	return (flag);
}

t_flag	flag_handler2(t_flag flag, char c)
{
	if (c == '0' && flag.right == 0 && flag.left == 0)
		flag.zero = 1;
	if (c == '*' && flag.pres == 0)
		flag.left_handle = 1;
	if (c == '*' && flag.pres == 1)
		flag.right_handle = 1;
	return (flag);
}

t_flag	flag_handler(t_flag flag, const char *p)
{
	int	i;

	i = 1;
	while (!is_conv(p[i]))
	{
		flag = flag_handler2(flag, p[i]);
		if (p[i] == '-' && flag.pres == 0 && flag.left_handle == 0)
		{
			flag.zero = 0;
			flag.left = 1;
		}
		if (flag.left_handle == 0 && flag.left == 0 && flag.pres == 0)
			if (ft_isdigit(p[i]))
				flag.right = 1;
		if (p[i] == '.')
			flag.pres = 1;
		if (flag.pres == 1 && flag.right_handle == 0 && ft_isdigit (p[i]))
			flag.pres_num = 1;
		if (p[i] == ' ')
			flag.space_flag = 1;
		i++;
	}
	return (flag);
}

t_flag	check_flag2(t_flag flag)
{
	if (flag.left == 1)
	{
		flag.right = 0;
		flag.zero = 0;
	}
	if (flag.right_handle == 1 && flag.pres_num == 1 && flag.left_handle == 1)
	{
		if (flag.before_dot < 0)
		{
			flag.left = 1;
			flag.zero = 0;
		}
		else
		{
			flag.right = 1;
		}
	}
	return (flag);
}

t_flag	check_star_left(t_flag flag)
{
	if (flag.before_dot < 0)
	{
		flag.zero = 0;
		flag.before_dot *= -1;
		flag.left = 1;
		flag.right = 0;
	}
	else if (flag.left == 0)
		flag.right = 1;
	flag = check_flag2(flag);
	if (flag.right_handle == 1)
		flag.pres_num = 1;
	if ((flag.pres == 1 && flag.after_dot > 0)
		|| (flag.pres == 1 && flag.pres_num == 0))
		flag.zero = 0;
	return (flag);
}
