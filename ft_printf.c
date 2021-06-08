#include "libft/libft.h"
#include "ft_printf.h"
#include <stdarg.h>



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

void handle_int(const char *p,char *out,t_flag flag,size_t length,t_params params)
{
	int count = 0;
	int width = ft_strlen(out);
	if(flag.left == 1)
		write(1,out,width);
	while(width < params.before_dot && (count <(params.before_dot -params.after_dot)))
	{
		ft_putchar_fd(' ',1);
		width++;
		count++;
	}
	while (width < params.after_dot)
	{
		ft_putchar_fd('0',1);
		width++;
	}
	if(flag.right == 1)
		write(1,out,ft_strlen(out));
}

int conv_length(const char *p,va_list argptr,int t,t_flag flag)
{
	t_params params;

	params = get_params(p,params,flag,argptr);
	flag = check_star_left(flag,params);
	// printf("haha %d \n",params.before_dot);
	int i = 0;
	char *out;
	while(!(is_conv(p[i])))
		i++;
	if(p[i] == 'd')
	{
			t = va_arg(argptr,int);
			out = ft_itoa(t);
			handle_int(p,out,flag,ft_strlen(out),params);
			free(out);
	}
	if(p[i] == 's')
	{
		out = va_arg(argptr,char *);
		return(ft_strlen(out));
	}
	if(p[i] == 'c')
	{
		return(1);
	}
	if(p[i] == 'u')
	{
		out_u_length(va_arg(argptr,long));
	}
	if(p[i] == 'X')
	{
		return(hex_length(va_arg(argptr,long)));
	}
	if(p[i] == 'x' || p[i] == 'X')
	{
		return(hex_length(va_arg(argptr,long)));
	}
	return(0);
}

int until_conv(const char *p)
{
	int i;

	i = 0;
	while(!is_conv(p[i]))
		i++;
	return(i);
}

int flag_out_put(t_flag flag,const char *p,va_list argptr,int i)
{
	int t;
	if(flag.left == 0 && flag.left_handle == 0 && flag.pres == 0 && flag.pres_num == 0 && flag.right == 0 && flag.right_handle == 0)
	{
		check_conv(p,argptr,t);
	}
	else
	{
		conv_length(p,argptr,i,flag);
	}
	return(0);
}

int ft_printf(const char *p,...)
{
	va_list argptr;
	int t;
	t_flag flag;
	va_start (argptr, p);
	int i = 0;
	size_t count = 0;
	char *len;
	while(*p)
	{
		if(*p == '%')
		{
			flag = init_flag(flag);
			flag = flag_handler(flag,p++);
			conv_length(p,argptr,t,flag);
			i = until_conv(p);
			p = p+i;
		}
		else
			write(1,p,1);
		p++;
	}
	return (0);
}

int main()
{
	ft_printf("%3.2d\n",2,2);
	printf("%3.2d\n",2);
}
