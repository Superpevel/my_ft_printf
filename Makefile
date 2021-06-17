LIBFT = ./libft/libft.a

N_TEMP = temp.a

NAME = libftprintf.a

SRCS =  ft_printf.c \
		hex_length.c \
		flag_start.c \
		ft_conv.c \
		print_u.c \
		put_hex.c \
		u_length.c \
		int_handle.c\
		char_handle.c\
		handle_s.c\
		handle_percent.c\
		handle_X.c\
		x_handle.c\
		u_handle.c\
		itoa_base.c\

SURPL_O = 	ft_printf.o \
		hex_length.o \
		flag_start.o \
		ft_conv.o \
		print_u.o \
		put_hex.o \
		u_length.o\
		int_handle.o\
		char_handle.o\
		handle_s.o\
		handle_percent.o\
		handle_X.o\
		x_handle.o\
		u_handle.o\
		itoa_base.o\
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
