#include "ft_printf.h"

t_flag	right_get(t_flag flag, va_list *argptr, int count, const char *p)
{
	char	*len;
	int		count1;

	count1 = count;
	if (flag.right_handle == 1)
		flag.after_dot = va_arg(*argptr, int);
	if (flag.pres == 1 && flag.pres_num == 1)
	{
		count1++;
		while (ft_isdigit(p[count1]))
			count1++;
		len = ft_substr(p, count + 1, count1 - 1);
		count = ft_atoi(len);
		flag.after_dot = count;
		free(len);
	}
	return (flag);
}

t_flag	left_start(t_flag flag, va_list *argptr, int count, const char *p)
{
	if (flag.left_handle == 1)
	{
		flag.before_dot = va_arg(*argptr, int);
		if (p[count] == '0')
			count++;
		while (!(ft_isdigit(p[count]) || is_conv(p[count])))
			count++;
		count--;
	}
	return (right_get(flag, argptr, count, p));
}

t_flag	get_params(const char *p, t_flag flag, va_list *argptr)
{
	char	*len;
	int		count;
	int		for_left;

	for_left = 0;
	count = 0;
	if (flag.left == 1)
	{
		count++;
		for_left++;
	}
	if (flag.left_handle == 0 && (flag.left == 1 || flag.right == 1))
	{
		if (p[for_left] == '-')
		{
			for_left++;
			count++;
		}
		while (ft_isdigit(p[count]))
			count++;
		len = ft_substr(p, for_left, count);
		flag.before_dot = ft_atoi(len);
		free(len);
	}
	return (left_start(flag, argptr, count, p));
}
