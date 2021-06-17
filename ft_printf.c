#include "libft/libft.h"
#include "ft_printf.h"
#include <stdarg.h>
#include <limits.h>
t_params get_params(const char *p,t_params params,t_flag flag,va_list *argptr)
{
	int t;

	char *len;
	int count,count1;
	int for_left = 0;
	int i ;
	count = 0;
	count1 = 0;

	if(flag.left==1)
	{
		count++;
		for_left++;
	}
	if(flag.left_handle == 0 && (flag.left == 1 || flag.right == 1))
	{
		if(p[for_left]== '-')
		{
			for_left++;
			count++;
		}
		while(ft_isdigit(p[count]))
			count++;
		len = ft_substr(p,for_left,count);
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

int handle_p(t_flag flag,t_params params,unsigned long long num)
{
	int spaces;
	int words = 0;
	int zeros;
	char *out;
	int i = 0;
	out = ft_ull_base(num,16);
	int len = ft_strlen(out) + 2;
	char *prefix = "0x";
	while (out[i] != '\0')
	{
		out[i] = ft_tolower(out[i]);
		i++;
	}
	
	zeros = x_zero(flag,params,num);
	if(zeros >= 0)
		return(zeros);
	else
		zeros =0;
	if(num != 0)
		words+=len;
	else
	{
		len = 3;
		words+=1;
	}
	if(flag.zero == 0)
	{
		zeros = params.after_dot - len;
		if(zeros>0)
			spaces = params.before_dot - zeros - len;
		else
			spaces = params.before_dot - len;
	}
	if(flag.zero == 1)
	{
		spaces = 0;
		zeros = params.before_dot - len;
	}
	if(flag.left == 1)
		while (zeros-- > 0)
		{
			ft_putchar_fd('0',1);
			words++;
		}
	if(flag.left == 1)
	{
		if(num != 0)
		{
			ft_putstr_fd(prefix,1);
			ft_putstr_fd(out,1);
		}
		else
		{
			ft_putstr_fd(prefix,1);
			ft_putstr_fd(out,1);
			words+=2;
		}
	}
	while (spaces-- > 0)
	{
		ft_putchar_fd(' ',1);
		words++;
	}
	if(flag.right == 1)
		while (zeros-- >0)
		{
			ft_putchar_fd('0',1);
			words++;
		}
	if(flag.right == 1)
	{
		if(num != 0)
		{
			ft_putstr_fd(prefix,1);
			ft_putstr_fd(out,1);
		}
		else
		{
			ft_putstr_fd(prefix,1);
			ft_putchar_fd('0',1);
			words = 3;
		}
	}
	free(out);
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
	// printf("params left %d \n",params.before_dot);
	// printf("\n");
	int i = 0;
	char *out;
	while(!(is_conv(p[i])))
		i++;
	if(p[i] == 'd' || p[i] == 'i')
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
		return(u_handle(flag,params,va_arg(*argptr,long)));
	}
	if(p[i] == 'X')
		return(handex_X(flag,params,va_arg(*argptr,long long)));
	if(p[i] == 'x')
		return(x_handle(flag,params,va_arg(*argptr,long long)));
	if(p[i] == '%')
		return(handle_per(flag,params));
	if(p[i] == 'p')
		return(handle_p(flag,params,va_arg(*argptr, unsigned long long)));
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
		t =ft_printf(" %.*s ", -1, NULL);
		printf("my fun %d\n",t);
		t= printf(" %.*s ", -1, NULL);
		printf("orgin %d\n",t);
	}
