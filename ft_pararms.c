#include "ft_printf.h"
#include "libft/libft.h"

t_params get_params(const char *p,t_params params,t_flag flag,va_list argptr)
{
	int t;

	char *len;
	int count,count1;
	int i ;
	count = 0;
	count1 = 0;
	if(flag.left==1)
		count++;
	if(flag.left_handle == 0 && (flag.left == 1 || flag.right == 1))
	{
		while(ft_isdigit(p[count]))
			count++;
		len = ft_substr(p,0,count);
		i = ft_atoi(len);
		params.before_dot = i;
		free(len);
	}
	else if(flag.left_handle == 1)
	{
		t =va_arg(argptr,int);

		params.before_dot= t;
		while (!(ft_isdigit(p[count]) || is_conv(p[count])))
			count++;
		count--;
	}
	count1 = count;
	if(flag.right_handle == 1)
	{
		params.after_dot= va_arg(argptr,int);
	}
	if(flag.pres == 1 && flag.pres_num == 1)
	{
		count1++;
		while(ft_isdigit(p[count1]))
			count1++;
		len = ft_substr(p,count+1,count1-1);
		i = ft_atoi(len);
		params.after_dot = i;
		free(len);
	}
	return(params);
}

t_params init_params(t_params params)
{
	params.after_dot = -1;
	params.before_dot = -1;
	params.minus_number = -1;
	return(params);
}