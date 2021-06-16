#include "libft/libft.h"
#include "printf.h"
#include <stdarg.h>
int put_length(long i ,int count )
{
	while (i>=10)
	{
		i = i /10;
		count++;
	}
	if(i<10)
	{
		count++;
	}
	return(count);
}

int out_u_length(long i)
{
	int count;

	count = 0;
	if(i<0)
	{
		return(put_length(4294967295 - i +1,count));
	}
	else
	{
		return(put_length(i,count));
	}
	return(count);
}