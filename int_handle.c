#include "ft_printf.h"
#include "libft/libft.h"

int handle_int(const char *p,char *out,t_flag flag,t_params params)
{
	int count = 0;
	int was_printed = 0;
	int width = ft_strlen(out);

	if(params.before_dot < 0 && flag.left ==1)
		params.before_dot = params.before_dot *-1;
	if(flag.left == 1 && flag.pres == 0)
	{
		write(1,out,width);
		was_printed += width;
	}
	if(params.after_dot > 0)
		count = params.before_dot - params.after_dot;
	else
		count = params.before_dot - width;
	if(params.minus_number == 1)
		count--;
	while(count>0 && flag.left != 1)
	{
		ft_putchar_fd(' ',1);
		was_printed++;
		count--;
	}
	count = params.after_dot - width;
	if(params.minus_number == 1)
		ft_putchar_fd('-',1);
	while (count>0)
	{
		ft_putchar_fd('0',1);
		count--;
		was_printed++;
	}
	if(flag.right == 1 || (flag.pres == 1 && flag.left == 1))
	{
		write(1,out,ft_strlen(out));
		was_printed+= ft_strlen(out);
	}
	if(flag.pres == 1 && flag.left == 1)
	{
		count = params.before_dot - was_printed;
		if(params.minus_number == 1)
			count--;
		while (count>0)
		{
			ft_putchar_fd(' ',1);
			count--;
			was_printed++;
		}
	}
	return(was_printed);
}
