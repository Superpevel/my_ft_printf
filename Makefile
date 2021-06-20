LIBFT = ./libft/libft.a

N_TEMP = temp.a

NAME = libftprintf.a

SRCS =  ft_printf.c \
		flag_start.c \
		ft_conv.c \
		int_handle.c\
		int_handle_2.c\
		char_handle.c\
		handle_s.c\
		handle_percent.c\
		handle_X.c\
		x_handle.c\
		u_handle.c\
		get_params.c\
		ft_itoa_base_long.c\
		ft_itoa_u.c\
		handle_p.c\

SURPL_O = 	ft_printf.o \
		flag_start.o \
		ft_conv.o \
		int_handle.o\
		int_handle_2.o\
		char_handle.o\
		handle_s.o\
		handle_percent.o\
		handle_X.o\
		x_handle.o\
		u_handle.o\
		get_params.o\
		ft_itoa_base_long.o\
		ft_itoa_u.o\
		handle_p.o\
CC = gcc

FLAGS = -c -Wall -Wextra -Werror

INCLUDES = -I./includes

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(MAKE) bonus -C ./libft
	cp libft/libft.a $(NAME)
	$(CC) $(FLAGS) $(INCLUDES) $(SRCS)
	ar -rcs $(NAME) $(OBJS)

all : $(NAME)

clean :
	$(MAKE) clean -C ./libft
	rm -rf $(SURPL_O)
	rm -rf $(OBJS)

fclean : clean
	$(MAKE) fclean -C ./libft
	rm -rf $(NAME)

re : fclean all
