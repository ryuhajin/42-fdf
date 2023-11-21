/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:17:11 by dayou             #+#    #+#             */
/*   Updated: 2023/11/21 18:59:30 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <stdio.h> //perror
# include <unistd.h>
# include <fcntl.h>
# include "./mlx/mlx.h"
# include "./libft/libft.h"
# include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

typedef enum e_status
{
	failed = -1,
	success = 0
}			t_status;
typedef enum e_read_status
{
	read_failed = -1,
	read_EOF = 0,
}			t_read_status;

typedef enum e_new_line_status
{
	no_new_line = 0,
	make_new_line = 1,
	line_malloc_failed = 2
}			t_make_line_status;
typedef struct s_img
{
	void * mlx_img; //mlx_img 는 mlx_new_image 함수가 반환하는 주소를 참조한다.
	char * addr;
	int bits_per_pixel; //픽셀 당 몇 비트가 할당되는가 //보통 ARGB는 알파벳 하나당 8비트. 즉 32비트 = 4바이트.
	int line_length; // 한 줄당 몇 바이트인가
	int endian;
} t_img; // mlx image를 사용하는데 필요한 모든 내용이 담긴 구조체
// mlx_new_image 함수는 공유 메모리 상에 가로, 세로 해상도 만큼의 공간을 할당하는듯. 도화지 생성?
// 이미지의 픽셀을 직접 변경하기 위해서는 메모리 상에 있는 이미지의 주소가 필요하다.

typedef struct s_data
{
	void * mlx_ptr;
	void * win_ptr;
	t_img img;
} t_data;

typedef struct s_init
{
	void * mlx;
	t_data * data;
	t_img * img;
	t_list * list;
}	t_init;

typedef struct s_vector
{
	int x;
	int y;
	int z;
}	t_vector;

// init.c
void	ft_perror(const char *str);
void	ft_lstiter_arg(t_list *lst,  void * arg, void (*f)(void *, void *));
t_init * all_init (void);
int fdf_map_check (t_init * init, char * file_name);
int fdf_file_open (t_init * init, char * file_name);
void remove_char_lst (void * list, void * c);

//init2.c
void content_del (void * content);
void split_del (void * content);
void remove_char (void * str, void * c);
void atoi_content (void * content);
void * ft_split_space (void * content);
int check_non_numeric_char(void * content);
int int_min_max_check(void * content);
int lst_true_false_check (t_list * list, int (*f)(void *));
void lst_atoi (void * content);
long long atolong (char * str);
int lst_column_check (t_list * list);

// input.c
int fdf_file_name_check (char * file_name);
int argc_argv_check (int argc, char * argv[]);

// line.c
void line_draw (int x1, int y1, int x2, int y2, t_img * img, int color);

// print.c
void print_str(void * str);
void print_int(void * num);
void print_map(void * map);
void print_lst_in_str (void * list);
void print_lst_in_int (void * list);
void print_lst_map (void * list);

//read_line.c
ssize_t	remainder_find_n(int fd, char **line, char remainder[][BUFFER_SIZE + 1]);
ssize_t	read_file(int fd, char **line, char remainder[][BUFFER_SIZE + 1]);
char	*read_flag_check(ssize_t flag, char *line);
char	*get_next_line(int fd);

//read_line2.c
char	*ft_strdup_gnl(char *s1);
char	*ft_strjoin_gnl(char *s1, char *s2, ssize_t size);
size_t	ft_strlcpy_gnl(char *dest, char *src);
ssize_t	find_newline(char *buff, ssize_t *size);

//main.c
void render_background (t_img * img, int color);
int	render(t_data *data, int x1, int x2, int y1, int y2, int color);
void img_pix_put (t_img * img, int x, int y, int color);
void line_draw (int x1, int y1, int x2, int y2, t_img * img, int color);

#endif
