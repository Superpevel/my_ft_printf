#include "libft/libft.h"
#include "ft_printf.h"


int is_conv(char p)
{
	if(p == 'd' || p == 's' || p == 'c' || p == 'u' || p == 'X' || p == 'x' || p=='%' || p == 'p' || p=='i')
		return(1);
	return(0);
}

