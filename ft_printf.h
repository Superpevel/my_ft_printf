#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft/libft.h"
# include <stdarg.h>
typedef struct s_flags
{
	int	pres;
	int	zero;
	int	left;
	int	right;
	int	left_handle;
	int	right_handle;
	int	pres_num;
	int	space_flag;
	int	before_dot;
	int	after_dot;
	int	int_minus;
	int	spaces;
	int	zeros;
}				t_flag;

void	hex(long quotient);
int		hex_length(long quotient);
void	hex_min(long quotient);
t_flag	flag_handler(t_flag flag, const char *p);
t_flag	init_flag(t_flag flag);
int		is_conv(char p);
void	check_conv(const char *p, va_list argptr, int t);
int		is_conv(char p);
t_flag	check_star_left(t_flag flag);
int		ft_printf(const char *p, ...);
int		handle_int(int t, t_flag flag);
int		print_char(char c, t_flag flag);
int		handle_s(char *out, t_flag flag);
int		handle_per(t_flag flag);
int		handle_X(t_flag flag, unsigned int num);
int		x_zero(t_flag flag, long num);
int		x_handle(t_flag flag, unsigned int num);
int		u_handle(t_flag flag, unsigned int num);
char	*ft_ull_base(unsigned long long ull, int base);
t_flag	get_params(const char *p, t_flag flag, va_list *argptr);
char	*ft_u_itoa(unsigned int n);
int		handle_p(t_flag flag, unsigned long long num);
int		ft_write(int s, int words, int what);
int		check_zero(int t, t_flag flag);
int		pls_work(t_flag flag, char *out);
int		words1(t_flag flag, int width, char *out);
char	*to_lower_str(char *hexa);
void	flag_params(int len, t_flag *flag);
#endif