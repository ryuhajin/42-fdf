CC = cc

# 1번 방법 : dyld 라이브러리 파일들이 존재하는 경로를 추가 (아래 주석 해제)
# export DYLD_LIBRARY_PATH = $(pwd)/mlx
# 2번 방법 : 실행파일과 같은 경로에 libmlx.dyld를 옮기기
# make -C mlx 다음 줄에 "cp libmlx.dyld ." 추가

SANITIZE = -fsanitize=address
CFLAG = -Wall -Werror -Wextra -g $(SANITIZE)

NAME = fdf

SRCS = main.c line.c

OBJS = $(SRCS:.c=.o)

MLX_DIR = ./mlx

all : $(NAME)

$(NAME) : $(OBJS)
		make all -C $(MLX_DIR) && cp $(MLX_DIR)/libmlx.dylib .
		$(CC) $(CFLAG) -L./mlx -lmlx -framework OpenGL \
		-framework Appkit $(OBJS) -o $(NAME)

%.o : %.c
	 $(CC) $(CFLAG) -c $^ -o $@

clean : 
		rm -rf $(OBJS)
		rm -rf libmlx.dylib
		make clean -C $(MLX_DIR)

fclean : clean 
	    rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
