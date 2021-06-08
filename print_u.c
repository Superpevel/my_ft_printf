#include "libft/libft.h"
#include "printf.h"
#include <stdarg.h>
void put(long i )
{
	if(i>=10)
	{
		put(i/10);
		ft_putchar_fd(i%10 + '0',1);
	}
	else if(i<10)
	{
		ft_putchar_fd(i%10 + '0',1);
	}
}

void out_u(long i)
{
	if(i<0)
	{
		put(4294967295 - i +1);
	}
	else
	{
		put(i);
	}
}