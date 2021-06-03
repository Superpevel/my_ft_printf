#include "libft/libft.h"
#include "printf.h"
#include <stdarg.h>


typedef struct s_flags
{
	int pres;
	int zero;
	int left;
	int right;
	int left_handle;
	int right_handle;
	int pres_num;
}				t_flag;



void hex(long quotient)
{
   char hexadecimalnum[100];
   long remainder;
   int j = 0;
   int i = 0;
    while (quotient != 0)
    {
        remainder = quotient % 16;
        if (remainder < 10)
            hexadecimalnum[j++] = 48 + remainder;
        else
            hexadecimalnum[j++] = 55 + remainder;
        quotient = quotient / 16;
    }
	i = j-1;
	while(i>=0)
	{
		ft_putchar_fd(hexadecimalnum[i],1);
		i--;
	}
}
void hex_min(long quotient)
{
   char hexadecimalnum[100];
   long remainder;
   int j = 0;
   int i = 0;
    while (quotient != 0)
    {
        remainder = quotient % 16;
        if (remainder < 10)
            hexadecimalnum[j++] = 48 + remainder;
        else
            hexadecimalnum[j++] = 87 + remainder;
        quotient = quotient / 16;
    }
	i = j-1;
	while(i>=0)
	{
		ft_putchar_fd(hexadecimalnum[i],1);
		i--;
	}
}

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

void put(long i ,int count i)
{
	if(i>=10)
	{
		put(i/10,count+1);
	}
	else if(i<10)
	{
		ft_putchar_fd(i%10 + '0',1);
	}
}

int out_u(long i)
{
	int count;

	count = 0;
	if(i<0)
	{
		return(put(4294967295 - i +1));
	}
	else
	{
		return(put(i),count);
	}
}

size_t check_conv(const char *p,va_list argptr,int t)
{
	char *out;
	if(*p == 'd')
	{
			t = va_arg(argptr,int);
			out = ft_itoa(t);
			write(1,out,ft_strlen(out));
			return(ft_strlen(out));
	}
	if(*p == 's')
	{
		out = va_arg(argptr,char *);
		write(1,out,ft_strlen(out));
		return(ft_strlen(out));
	}
	if(*p == 'c')
	{
		ft_putchar_fd(va_arg(argptr,int ),1);
		return(1);
	}
	if(*p == 'u')
	{
		out_u(va_arg(argptr,long));
	}
	if(*p == 'X')
	{
		hex(va_arg(argptr,long));
	}
	if(*p == 'x')
	{
		hex_min(va_arg(argptr,long));
	}
	return(0);
}


size_t conv_length(const char *p,va_list argptr,int t)
{
	char *out;
	if(*p == 'd')
	{
			t = va_arg(argptr,int);
			out = ft_itoa(t);
			return(ft_strlen(out));
	}
	if(*p == 's')
	{
		out = va_arg(argptr,char *);
		return(ft_strlen(out));
	}
	if(*p == 'c')
	{
		return(1);
	}
	if(*p == 'u')
	{
		out_u(va_arg(argptr,long));
	}
	if(*p == 'X')
	{
		hex(va_arg(argptr,long));
	}
	if(*p == 'x')
	{
		hex_min(va_arg(argptr,long));
	}
	return(0);
}


int is_conv(char p)
{
	if(p == 'd' || p == 's' || p == 'c' || p == 'u' || p == 'X' || p == 'x')
		return(1);
	return(0);
}

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
	int t;
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

int until_conv(const char *p)
{
	int i;

	i = 0;
	while(!is_conv(p[i]))
		i++;
	return(i);
}

int left_out(const char *p,va_list argptr,int rolling)
{
	char *len;
	int  i;
	int count;
	int t;
	count = 0;
	// printf("%s","I WAS HERE \n");
	p++;
	while(ft_isdigit(p[count]))
		count++;
	len = ft_substr(p,0,count);
	i = ft_atoi(len);
	p = p+count;
	count = check_conv(p,argptr,t);
	i = i-count;
	if(i > 0)
		while(i)
		{
			ft_putchar_fd(' ',1);
			i--;
		}
	return(0);
}

int right_out()
{
	int t = ;
}

int flag_out_put(t_flag flag,const char *p,va_list argptr,int i)
{
	int t;
	// printf("flags left %d \n",flag.left);
	// printf("flags left_handle %d \n",flag.left_handle);
	// printf("flags right_handle %d \n",flag.right_handle);
	// printf("flags right %d \n",flag.right);
	// printf("flags pres %d \n",flag.pres);
	// 	printf("flags pres num %d \n",flag.pres_num);
	if(flag.left == 0 && flag.left_handle == 0 && flag.pres == 0 && flag.pres_num == 0 && flag.right == 0 && flag.right_handle == 0)
		check_conv(p,argptr,t);
	if(flag.left == 1 && flag.left_handle == 0 && flag.pres == 0 && flag.pres_num == 0 && flag.right == 0 && flag.right_handle == 0)
	{
		left_out(p,argptr,i);
	}
	if(flag.left == 0 && flag.left_handle == 0 && flag.pres == 0 && flag.pres_num == 0 && flag.right == 1 && flag.right_handle == 0)
		right_out(p,argptr,i);
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
	char *out;
	while(*p)
	{
		if(*p == '%')
		{

			flag = init_flag(flag);
			flag = flag_handler(flag,p++);
			flag_out_put(flag,p,argptr,t);
			i = until_conv(p);
			p = p+i;
		}
		else
		{
			write(1,p,1);
		}
		p++;
	}
	return (0);
}
int main()
{
	ft_printf("%x\n",1);
	printf("%x\n",1);
}
