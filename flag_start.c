#include "ft_printf.h"
#include "libft/libft.h"
t_flag init_flag(t_flag flag)
{
	flag.pres = 0;
	flag.zero = 0;
	flag.left = 0;
	flag.right = 0;
	flag.left_handle = 0;
	flag.right_handle = 0;
	flag.pres_num = 0;
	return(flag);
}
t_flag flag_handler(t_flag flag,const char *p)
{
	int i;
	i = 0;
	while(!is_conv(p[i]))
	{
		if(p[i] == '*' && flag.pres == 0)
				flag.left_handle = 1;
		if(p[i] == '*' && flag.pres == 1)
				flag.right_handle = 1;
		if(p[i] == '-' && flag.pres == 0 && flag.left_handle == 0)
			flag.left = 1;
		if(flag.left_handle == 0 && flag.left == 0 && flag.pres == 0 && ft_isdigit(p[i]))
			flag.right = 1;
		if(p[i] == '.')
			flag.pres = 1;
		if(flag.pres == 1 && flag.right_handle == 0 && ft_isdigit (p[i]))
			flag.pres_num = 1;
		i++;
	}
	// printf("flags left %d \n",flag.left);
	// printf("flags left_handle %d \n",flag.left_handle);
	// printf("flags right_handle %d \n",flag.right_handle);
	// printf("flags right %d \n",flag.right);
	// printf("flags pres %d \n",flag.pres);
	// 	printf("flags pres num %d \n",flag.pres_num);
	return(flag);
}


t_flag check_star_left(t_flag flag,t_params *params)
{
	if(params->before_dot<0)
	{
		params->before_dot *= -1;
		flag.left = 1;
	}
	else
		flag.right = 1;
	return(flag);
}