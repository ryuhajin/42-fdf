/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 20:51:29 by dayou             #+#    #+#             */
/*   Updated: 2023/11/28 21:44:19 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_leak(void)
{
	system("leaks --list -- fdf");
}

t_idx	* zero_vec(t_idx	*vec)
{
	vec->x = 0;
	vec->y = 0;
	return (vec);
}

void	*rec_malloc(size_t unit, int count[], int depth)
{
	void	**ptr;
	int		idx;

	if (depth == 1)
		return (malloc(unit * (*count)));
	ptr = malloc(sizeof(void *) * (*count + 1));
	ptr[*count] = NULL;
	idx = 0;
	while (idx < *count)
	{
		ptr[idx] = rec_malloc(unit, count + 1, depth - 1);
		idx++;
	}
	return (ptr);
}

void	rec_free(void *ptr, int depth)
{
	void	**dptr;

	if (depth == 0)
		return ;
	if (depth > 1)
	{
		dptr = ptr;
		while (*dptr != NULL)
		{
			rec_free(*dptr, depth - 1);
			++dptr;
		}
	}
	free(ptr);
}

t_vector	***lst_change_to_arr(t_list *lst)
{
	t_vector***const	arr
		= rec_malloc(sizeof(t_vector),
			(int []){ft_lstsize(lst), ft_lstsize(lst->content), 1}, 3);
	t_idx	index;
	t_list	*inner_list;

	zero_vec(&index);
	index.y = 0;
	while (arr[index.y] != NULL)
	{
		index.x = 0;
		inner_list = (t_list *)lst->content;
		while (arr[index.y][index.x] != NULL)
		{
			arr[index.y][index.x]->x = ((t_vector *)inner_list->content)->x;
			arr[index.y][index.x]->y = ((t_vector *)inner_list->content)->y;
			arr[index.y][index.x]->z = ((t_vector *)inner_list->content)->z;
			inner_list = inner_list->next;
			index.x++;
		}
		lst = lst->next;
		index.y++;
	}
	return (arr);
}

void	print_vec(void *pvec)
{
	t_vector*const	vec = pvec;

	printf("[%f %f %f]", vec->x, vec->y, vec->z);
}

void	ft_arriter(void ** arr, void (*f)(void *))
{
	unsigned int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		f(arr[i]);
		i++;
	}
}

void	print_line(void *parr)
{
	void**const	arr = parr;
	ft_arriter(arr, print_map);
	printf("\n");
}

void draw_line(t_vector ***arr, t_img *img)
{
	t_idx	index;

	zero_vec(&index);
	while (arr[index.y] != NULL)
	{
		index.x = 0;
		while (arr[index.y][index.x] != NULL)
		{
			if (arr[index.y + 1] != NULL)
				line_draw(img, arr[index.y][index.x], arr[index.y + 1][index.x]);
			if (arr[index.y][index.x + 1] != NULL)
				line_draw(img, arr[index.y][index.x], arr[index.y][index.x + 1]);
			index.x++;
		}
		index.y++;
	}
}

void isometric_xyz (t_list * list, float * zratio)
{
	while (list != NULL)
	{
		ft_lstiter_arg(list->content, (void *)zratio, xyz_change_isometric_coodinate);
		list = list->next;
	}	
}


float get_scale_point(t_vector p1, t_vector p2, t_vector p3)
{
	float scale;
	float img_width;
	float img_height;
	float zratio;

	zratio = 0.0f;
	xyz_change_isometric_coodinate((void *)&p1, (void *)&zratio);
	xyz_change_isometric_coodinate((void *)&p2, (void *)&zratio);
	xyz_change_isometric_coodinate((void *)&p3, (void *)&zratio);
	img_width = fabsf(p1.x - p3.x);
	img_height = fabsf(p2.y);

	scale = WIDTH / img_width;
	if (scale > HEIGHT / img_height)
		scale = HEIGHT / img_height;
	return scale * 0.6;
}

void move_x (void * pvec, void * arg)
{
	t_vector * vec = pvec;
	int * move_x = arg;

	vec->x += *move_x;
}

void move_y (void * pvec, void * arg)
{
	t_vector * vec = pvec;
	int * move_y = arg;

	vec->y += *move_y;
}

void move_loop_x (void * lst, void * arg)
{
	t_list * list = lst;
	ft_lstiter_arg(list, arg, move_x);
}

void move_loop_y (void * lst, void * arg)
{
	t_list * list = lst;
	ft_lstiter_arg(list, arg, move_y);
}

void sv(void *pvec, void *arg)
{
	t_vector	*vec = pvec;
	float		*scale = arg;

	vec->x *= *scale;
	vec->y *= *scale;
}

void scale_loop(void *plst, void *arg)
{
	t_list *lst = plst;
	ft_lstiter_arg(lst, arg, sv);
}

void vector_scaling_lst (t_init * init, float * scale)
{
	*scale = get_scale_point(*(t_vector *)(P1), *(t_vector *)(P2), *(t_vector *)(P3));
	if (*scale > 30.0f)
		*scale *= 0.6;
	else
		*scale *= 1.2;
	ft_lstiter_arg(init->list, (void *)scale, scale_loop);
}

void vector_move_in_window (t_init * init)
{
	t_point move_xy;

	move_xy.x = get_move_x_point(*(t_vector *)(P1), *(t_vector *)(P3));
	ft_lstiter_arg(init->list, (void *)&move_xy.x, move_loop_x);
	move_xy.y = get_move_y_point(*(t_vector *)(P2));
	ft_lstiter_arg(init->list, (void *)&move_xy.y, move_loop_y);
}

void init_free_perror(t_init * init, char * str)
{
	double_lst_clear(init->list, content_del);
	free(init->data);
	free(init);
	ft_perror(str);
}
void init_free(t_init * init)
{
	rec_free(init->map, 3);
	free(init->data);
	free(init);
}

void clean(t_init *init)
{
	mlx_destroy_image(init->mlx, init->data->img.mlx_img);
	mlx_destroy_window(init->mlx, init->data->win_ptr);
	init_free(init);
}

int close_window (int key, t_init * init)
{
	if (key == 53)
	{
		clean(init);
	}
	return 0;
}

int close_window_ondestroy(t_init * init)
{
	clean(init);
	return 1;
}

void vector_setting_for_lender (t_init * init)
{
	float scale;
	
	vector_scaling_lst(init, &scale);
	isometric_xyz(init->list, &scale);
	vector_move_in_window(init);
}

/*
 * This function will be called if the X button @ GUI window is pressed.
 * This function should clearly kill everything and free every single memory
 * @param init t_init struture that contains every nessery datas
 */
// int	test(void *init)
// {
// 	close_window(17, init);
// 	return 1;
// }

void make_map_arry (t_init * init)
{
	init->map = lst_change_to_arr(init->list);
	double_lst_clear(init->list, content_del);
}

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int	close_mlx(int keycode, t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}


int main(int argc, char * argv[])
{
	// t_init * init;

	// atexit(check_leak);
	// if (argc_argv_check (argc, argv) == failed)
	// 	ft_perror("file error\n");
	// init = all_init();
	// if (init == NULL)
	// 	ft_perror("error\n");
	// if (fdf_map_check (init, argv[1]) == failed)
	// 	init_free_perror(init, "map error\n");
	// if (make_vector_list(init) == failed)
	// 	init_free_perror(init, "error\n");
	
	// vector_setting_for_lender(init);
	// make_map_arry(init);
	
	// draw_line(init->map, init->img);
	
	// mlx_put_image_to_window(init->mlx, init->data->win_ptr, init->data->img.mlx_img, 0, 0);
	// mlx_key_hook(init->data->win_ptr, close_window, init);
	// mlx_hook(init->data->win_ptr, 17, 0, close_window_ondestroy, init);
	// mlx_loop(init->mlx);
	// printf("end\n");
	// init_free(init);
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	mlx_hook(vars.win, 2, 1L<<0, close_mlx, &vars);
	// mlx_hook(vars.win, 17, 0, close_window_ondestroy, NULL);
	mlx_loop(vars.mlx);
	return 0;
}
