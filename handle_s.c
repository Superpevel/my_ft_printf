#include "libft/libft.h"
#include "ft_printf.h"

int handle_s(char *out,t_params params ,t_flag flag)
{
	int words = 0;
	int spaces = 0;
	int pres;
	int i = 0;

	if (!out)
		out = "(null)";
	if(params.after_dot > 0)
	{
		if(params.after_dot < (int)ft_strlen(out))
			pres = params.after_dot;
		else
			pres = ft_strlen(out);
	}
	else if((params.after_dot == 0 && flag.pres == 1) || (flag.pres == 1 && flag.pres_num == 0))
		pres = 0;
	else
		pres = ft_strlen(out);
	spaces = params.before_dot - pres;
	if(flag.left == 1)
	{
		while (i < pres)
		{
			ft_putchar_fd(out[i],1);
			i++;
			words++;
		}	
	}
	while (spaces-- > 0)
	{
		ft_putchar_fd(' ',1);
		words++;
	}
	if(flag.right == 1)
	{
		while (i < pres)
		{
			ft_putchar_fd(out[i],1);
			i++;
			words++;
		}	
	}
	return(words);
}