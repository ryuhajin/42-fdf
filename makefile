CC = cc

# SANITIZE = -fsanitize=address
CFLAG = -Wall -Werror -Wextra -g $(SANITIZE)

NAME = fdf

SRCS = main_test.c free.c init.c init2.c input.c \
	isometric.c line.c map_check.c map_check2.c map.c \
	move.c mlx_event.c print.c read_line.c read_line2.c \
	scale.c utils.c utils2.c

OBJS = $(SRCS:.c=.o)

MLX_DIR = ./mlx

LIBFT_DIR = ./libft/

all : $(NAME)

$(NAME) : $(OBJS)
		make all -C $(LIBFT_DIR)
		make all -C $(MLX_DIR) && cp $(MLX_DIR)/libmlx.dylib .
		$(CC) $(CFLAG) -L./libft -lft -L./mlx -lmlx -framework OpenGL \
		-framework Appkit $(OBJS) -o $(NAME)

%.o : %.c
	 $(CC) $(CFLAG) -c $^ -o $@

clean : 
		rm -rf $(OBJS)
		rm -rf libmlx.dylib
		make clean -C $(LIBFT_DIR)
		make clean -C $(MLX_DIR)

oclean :
		rm -rf $(OBJS)

fclean : clean 
	    rm -rf $(NAME)

ore : oclean
	make

re : fclean all

.PHONY : all clean fclean re oclean
