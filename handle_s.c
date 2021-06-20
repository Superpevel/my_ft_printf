#include "ft_printf.h"

int	check_pres(int pres, char *out, t_flag flag)
{
	if (flag.after_dot > 0)
	{
		if (flag.after_dot < (int)ft_strlen(out))
			pres = flag.after_dot;
		else
			pres = ft_strlen(out);
	}
	else if ((flag.after_dot == 0 && flag.pres == 1)
		|| (flag.pres == 1 && flag.pres_num == 0))
		pres = 0;
	else
		pres = ft_strlen(out);
	return (pres);
}

int	right_s(int words, int pres, t_flag flag, char *out)
{
	int	i;

	i = 0;
	if (flag.right == 1)
	{
		while (i < pres)
		{
			ft_putchar_fd(out[i], 1);
			i++;
			words++;
		}
	}
	return (words);
}

int	handle_s(char *out, t_flag flag)
{
	int	words;
	int	spaces;
	int	pres;
	int	i;

	i = 0;
	words = 0;
	spaces = 0;
	pres = 0;
	if (!out)
		out = "(null)";
	pres = check_pres(pres, out, flag);
	spaces = flag.before_dot - pres;
	if (flag.left == 1)
	{
		while (i < pres)
		{
			ft_putchar_fd(out[i], 1);
			i++;
			words++;
		}
	}
	words = ft_write(spaces, words, 1);
	words = right_s(words, pres, flag, out);
	return (words);
}
