#include "ft_printf.h"

int	conv_length(const char *p, va_list *argptr, t_flag flag)
{
	int	i;

	i = 0;
	flag = get_params(p, flag, argptr);
	flag = check_star_left(flag);
	while (!(is_conv(p[i])))
		i++;
	if (p[i] == 'd' || p[i] == 'i')
		return (handle_int(va_arg(*argptr, int), flag));
	if (p[i] == 's')
		return (handle_s(va_arg(*argptr, char *), flag));
	if (p[i] == 'c')
		return (print_char(va_arg(*argptr, int), flag));
	if (p[i] == 'u')
		return (u_handle(flag, va_arg(*argptr, long)));
	if (p[i] == 'X')
		return (handle_X(flag, va_arg(*argptr, long long)));
	if (p[i] == 'x')
		return (x_handle(flag, va_arg(*argptr, unsigned int)));
	if (p[i] == '%')
		return (handle_per(flag));
	if (p[i] == 'p')
		return (handle_p(flag, va_arg(*argptr, void *)));
	return (0);
}

int	until_conv(const char *p)
{
	int	i;

	i = 0;
	while (!is_conv(p[i]))
		i++;
	return (i);
}

t_flag	flag_starter(t_flag flag, const char *p)
{
	flag = init_flag(flag);
	flag = flag_handler(flag, p);
	return (flag);
}

int	ft_printf(const char *p, ...)
{
	int			i;
	size_t		count;
	va_list		argptr;
	t_flag		flag;

	va_start (argptr, p);
	i = 0;
	count = 0;
	while (*p)
	{
		if (*p == '%')
		{
			flag = flag_starter(flag, p++);
			count += conv_length(p, &argptr, flag);
			i = until_conv(p);
			p = p + i;
		}
		else
		{
			write(1, p, 1);
			count++;
		}
		p++;
	}
	return (count);
}
