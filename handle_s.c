#include "libft/libft.h"
#include "ft_printf.h"

int handle_s(char *out,t_params params ,t_flag flag)
{
	int words = 0;
	int spaces = 0;
	int i = 0;

	if (!out)
		out = "(null)";
	int width = ft_strlen(out);
	if(flag.pres && (params.after_dot == 0 || flag.pres_num == 0))
			spaces = params.before_dot;
	if(width < params.after_dot && flag.pres == 1)
	{
		spaces = params.before_dot - width;
	}
	if(flag.pres == 0 && (flag.left == 1 || flag.right == 1))
		spaces = params.before_dot - width;
	if(flag.pres == 1 && flag.right == 1 && flag.pres_num == 1)
	{
		if(width < params.after_dot)
			spaces = params.before_dot - width;
		else
			spaces = params.before_dot - params.after_dot;
	}
	if(flag.pres == 1 && flag.left == 1 && flag.pres_num == 1)
	{
		if(width < params.after_dot)
			spaces = params.before_dot - width;
		else
			spaces = params.before_dot - params.after_dot;
	}
	if(flag.pres == 1 && flag.pres_num == 0 && flag.right == 0 && flag.left == 0)
	{
		spaces = params.before_dot;
		while (spaces-- > 0)
			ft_putchar_fd(' ',1);
		return(params.before_dot);
	}
	if((flag.left == 1 || flag.right == 1) && flag.pres == 1 && width > params.after_dot)
			spaces = params.before_dot - params.after_dot;
	if(params.after_dot < 0)
		spaces = 0;
	if (flag.left == 1)
	{
		while (out[i] != '\0')
		{
			if(flag.pres == 1 && i >= params.after_dot)
				break;
			ft_putchar_fd(out[i],1);
			words++;
			i++;
		}
	}
	while (spaces > 0)
	{
		ft_putchar_fd(' ',1);
		spaces--;
		words++;
	}
	if (flag.right == 1)
	{
		i = 0;
		while (out[i] != '\0' )
		{
			if(flag.pres == 1 && i >= params.after_dot)
				break;
			ft_putchar_fd(out[i],1);
			words++;
			i++;
		}
	}
	return(words);
}