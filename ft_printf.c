#include "libft/libft.h"
#include "ft_printf.h"
#include <stdarg.h>
#include <limits.h>
t_params get_params(const char *p,t_params params,t_flag flag,va_list *argptr)
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
		t =va_arg(*argptr,int);

		params.before_dot= t;
		if(p[count] == '0') //11
			count++;
		while (!(ft_isdigit(p[count]) || is_conv(p[count])))
			count++;
		count--;
	}
	count1 = count;
	if(flag.right_handle == 1)
	{
		params.after_dot= va_arg(*argptr,int);
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

int handle_s(char *out,t_params params ,t_flag flag)
{
	int words = 0;
	int spaces = 0;
	int i = 0;
	int width = ft_strlen(out);
	if(width > params.after_dot)
		spaces = params.before_dot - width;
	else
		spaces = params.before_dot - params.after_dot;
	if(flag.pres == 1 && flag.pres_num == 0)
	{
		spaces = params.before_dot;
		while (spaces-- > 0)
			ft_putchar_fd(' ',1);
		return(params.before_dot);
	}
	if (flag.left == 1)
	{
		while (out[i] != '\0')
		{
			if(flag.pres == 1 && i >= params.after_dot)
				break;
			ft_putchar_fd(out[i],1);
			words++;
			i++;
		}
	}
	while (spaces > 0)
	{
		ft_putchar_fd(' ',1);
		spaces--;
		words++;
	}
	if (flag.right == 1)
	{
		while (out[i] != '\0' )
		{
			if(flag.pres == 1 && i >= params.after_dot)
				break;
			ft_putchar_fd(out[i],1);
			words++;
			i++;
		}
	}
	return(words);
}

int conv_length(const char *p,va_list *argptr,int t,t_flag flag)
{
	t_params params;
	params.after_dot = 0;
	params.before_dot = 0;
	t= 0;
	params = get_params(p,params,flag,argptr);
	flag = check_star_left(flag,&params);
	// printf("flags left %d \n",flag.left);
	// printf("flags left_handle %d \n",flag.left_handle);
	// printf("flags right_handle %d \n",flag.right_handle);
	// printf("flags right %d \n",flag.right);
	// printf("flags pres %d \n",flag.pres);
	// printf("flags pres num %d \n",flag.pres_num);
	// printf("flags zeo %d \n",flag.zero);
	// printf("\n");
	int i = 0;
	char *out;
	while(!(is_conv(p[i])))
		i++;
	if(p[i] == 'd')
	{
		return(handle_int(va_arg(*argptr,int),flag,params));
	}
	if(p[i] == 's')
	{
		out = va_arg(*argptr,char *);
		return(handle_s(out,params,flag));
	}
	if(p[i] == 'c')
	{
		return(print_char(va_arg(*argptr,int),flag,params));
	}
	if(p[i] == 'u')
	{
		out_u_length(va_arg(*argptr,long));
	}
	if(p[i] == 'X')
	{
		return(hex_length(va_arg(*argptr,long)));
	}
	if(p[i] == 'x' || p[i] == 'X')
	{
		return(hex_length(va_arg(*argptr,long)));
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

int ft_printf(const char *p,...)
{
	va_list argptr;
	int t;
	t = 0;
	t_flag flag;
	va_start (argptr, p);
	int i = 0;
	size_t count = 0;
	while(*p)
	{
		if(*p == '%')
		{
			flag = init_flag(flag);
			flag = flag_handler(flag,p++);
			count += conv_length(p,&argptr,t,flag);
			i = until_conv(p);
			p = p+i;
		}
		else
		{
			write(1,p,1);
			count++;
		}
		p++;
	}
	return (count);
}

int main()
{
	int t;
	t =ft_printf(" %3.0s\n", "123");
	printf("my fun %d\n",t);
	t= printf(" %3.0s\n", "123");
	printf("origin %d\n",t);
}
