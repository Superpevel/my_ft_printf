#include "libft/libft.h"
#include "printf.h"
#include <stdarg.h>
int put_length(long i ,int count )
{
	if(i>=10)
	{
		put_length(i/10,count+1);
	}
	else if(i<10)
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
}