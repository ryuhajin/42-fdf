/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:17:11 by dayou             #+#    #+#             */
/*   Updated: 2023/11/29 22:28:56 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./libft/libft.h"
# include "./mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h> //perror
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# ifndef COS_30
#  define COS_30 0.86602540378f
# endif

# ifndef ESC
#  define ESC 53
# endif

# ifndef DESTROY_EVENT
#  define DESTROY_EVENT 17
# endif

# ifndef P1
#  define P1 ft_lstlast(init->list->content)->content
# endif

# ifndef P2
#  define P2 ft_lstlast(ft_lstlast(init->list)->content)->content
# endif

# ifndef P3
#  define P3 ((t_list *)ft_lstlast(init->list)->content)->content
# endif

# ifndef WIDTH
#  define WIDTH 1920
# endif

# ifndef HEIGHT
#  define HEIGHT 1080
# endif

# ifndef WHITE
#  define WHITE 0xFFFFFF
# endif

typedef enum e_status
{
	failed = -1,
	success = 0
}				t_status;
typedef enum e_read_status
{
	read_failed = -1,
	read_EOF = 0,
}				t_read_status;

typedef enum e_new_line_status
{
	no_new_line = 0,
	make_new_line = 1,
	line_malloc_failed = 2
}				t_make_line_status;

typedef struct s_img
{
	void		*mlx_img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
}				t_data;

typedef struct s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

typedef struct s_idx
{
	int			x;
	int			y;
}				t_idx;
typedef t_idx	t_point;

typedef struct s_init
{
	void		*mlx;
	t_data		*data;
	t_img		*img;
	t_list		*list;
	t_vector	***map;
}				t_init;

//free.c
void	init_free(t_init *init);
void	double_lst_free_for_error(t_init *init, char *str);
void	init_map_arry_free(t_init *init);
void	rec_free(void *ptr, int depth);

//init.c
t_init	*data_init(t_init *init, t_data *data);
t_init	*all_init(void);

//init2.c
void	*make_vector_node(void *list);
void	set_xy_in_vector_lst(void *list, void *vector);
void	make_vector_list(t_init *init);

//input.c
int				newline_check(void *node);
int				fdf_file_name_check(char *file_name);
int				fdf_file_open(t_init *init, char *file_name);
void			argc_argv_check(int argc, char *argv[], t_init **init);

//isometric.c
void	vector_scaling_lst(t_init *init, float *scale);
void	isometric_xyz(t_list *list, float *zratio);
void	xyz_change_isometric_coodinate(void *content, void *zratio);

//line.c
void			img_pix_put(t_img *img, int x, int y);
void			dot_on_pixel(t_img *img, t_vector *v1, t_vector *v2);
void			x_plus_pixel_put(t_point v1, t_point v2, t_img *img);
void			y_plus_pixel_put(t_point v1, t_point v2, t_img *img);
void			line_draw(t_vector ***arr, t_img *img);

//map_check.c
void	*ft_split_space(void *content);
int	check_non_numeric_char(void *list);
int	int_min_max_check(void *list);
int	lst_column_check(t_list *list);
int	fdf_map_check(t_init *init);

//map_check2.c
void	remove_char(void *str, void *c);
void	remove_char_lst(void *list, void *c);
long long	atolong(char *str);
void	lst_atoi(void *content);

//map.c
void			ft_arriter(void **arr, void (*f)(void *));
t_vector		***alloc_map(int y, int x);
void			lst_change_to_arr(t_list *lst, t_vector ***map);
void			make_map_arry(t_init *init);
void			vector_setting_for_render(t_init *init);

//mlx_event.c
void	clean(t_init *init);
int	close_window(int key, t_init *init);
int	close_window_ondestroy(t_init *init);

//move.c
int				get_move_x_point(t_vector p1, t_vector p3);
int				get_move_y_point(t_vector p2);
void			move_loop(void *lst, void *arg);
void			move_xy(void *pvec, void *arg);
void			vector_move_in_window(t_init *init);

//print.c
void			print_str(void *str);
void			print_int(void *num);
void			print_map(void *map);
void			print_lst_in_str(void *list);
void			print_lst_in_int(void *list);
void			print_lst_map(void *list);

//read_line.c
ssize_t			remainder_find_n(int fd, char **line,
					char remainder[][BUFFER_SIZE + 1]);
ssize_t			read_file(int fd, char **line, char remainder[][BUFFER_SIZE
					+ 1]);
char			*read_flag_check(ssize_t flag, char *line);
char			*get_next_line(int fd);

//read_line2.c
char			*ft_strdup_gnl(char *s1);
char			*ft_strjoin_gnl(char *s1, char *s2, ssize_t size);
size_t			ft_strlcpy_gnl(char *dest, char *src);
ssize_t			find_newline(char *buff, ssize_t *size);

//scale.c
void	xy_scale_change(void *pvec, void *arg);
void	scale_loop(void *plst, void *arg);
float	get_scale_point(t_vector p1, t_vector p2, t_vector p3);

//utils.c
void			content_del(void *content);
void			double_lst_clear(t_list *list, void (*del)(void *));
void			ft_lstiter_arg(t_list *lst, void *arg, void (*f)(void *,
						void *));
int				lst_true_false_check(t_list *list, int (*f)(void *));

//utils2.c
void			ft_perror(const char *str);
t_idx			*zero_vec(t_idx *vec);
void			ft_vector_swap(t_point *a, t_point *b);

#endif
