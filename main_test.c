/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 20:51:29 by dayou             #+#    #+#             */
/*   Updated: 2023/11/24 22:05:25 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector	*zero_vec(t_vector	*vec)
{
	vec->x = 0;
	vec->y = 0;
	vec->z = 0;
	return (vec);
}

/*
allocate n-dimension memory.
NULL-terminated.
usage: rec_malloc(sizeof(t_vector), (int[]){size_y, size_x}, 2);
*/
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

/*
free n-dimension memory.
more than 1-dimension pointer sholud be NULL-terminated.
*/
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

t_vector	***lst_to_arr(t_list *lst)
{
	t_vector***const	arr
		= rec_malloc(sizeof(t_vector),
			(int []){ft_lstsize(lst), ft_lstsize(lst->content), 1}, 3);
	t_vector			index;
	t_list				*inner_list;

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

	printf("[%d %d %d]", vec->x, vec->y, vec->z);
}

/*
get array of pointer,
call function for each pointer
*/
void	ft_arriter(void **arr, void (*f)(void *))
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
	t_vector	index;

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

/*-----------=---=-=-=-=-=-=-=-=-=-=-=-=-*/

void iso_lst (t_init * init)
{
	t_list * list;
	float filter;
	
	list = init->list;
	filter = 12.0;
	while (list != NULL)
	{
		ft_lstiter_arg(list->content, (void *)&filter, xyz_change_isometric_coodinate);
		list = list->next;
	}	
}

void scale_vec(void *pvec)
{
	t_vector *vec = pvec;

	vec->x *= 50;
	vec->y *= 50;
}

void scale_loop(void *plst)
{
	t_list *lst = plst;
	ft_lstiter(lst, scale_vec);
}

int main(int argc, char * argv[])
{
	t_init * init;

	
	if (argc_argv_check (argc, argv) == failed)
	{
		printf("argc argv error\n");
		return 0;
	}
	init = all_init();
	if (init == NULL)
	{
		printf("init error\n");
		return 0;
	}
	if (fdf_map_check (init, argv[1]) == failed)
	{
		printf("input error\n");
		return 0;
	}
	if (make_vector_list(init) == failed)
	{
		printf("vector error\n");
		return 0;
	}
	ft_lstiter(init->list, scale_loop);
	ft_lstiter(init->list, print_lst_map);
	iso_lst(init);
	t_vector ***arr = lst_to_arr(init->list);
	ft_arriter((void **)arr, print_line);
	draw_line(arr, init->img);
	// line_draw_lst(init);
	
	// test line draw
	// t_vector v1, v2;
	// v1.x = 200;
	// v1.y = 100;
	
	// v2.x = 200;
	// v2.y = 0;
	// line_draw(init->img, &v1, &v2);
	// v2.x = 260;
	// v2.y = 0;
	// line_draw(init->img, &v1, &v2);
	// v2.x = 300;
	// v2.y = 0;
	// line_draw(init->img, &v1, &v2);
	// v2.x = 300;
	// v2.y = 40;
	// line_draw(init->img, &v1, &v2);
	// v2.x = 300;
	// v2.y = 100;
	// line_draw(init->img, &v1, &v2);
	// v2.x = 300;
	// v2.y = 160;
	// line_draw(init->img, &v1, &v2);
	// v2.x = 300;
	// v2.y = 200;
	// line_draw(init->img, &v1, &v2);
	// v2.x = 260;
	// v2.y = 200;
	// line_draw(init->img, &v1, &v2);
	// v2.x = 200;
	// v2.y = 200;
	// line_draw(init->img, &v1, &v2);
	// v2.x = 140;
	// v2.y = 200;
	// line_draw(init->img, &v1, &v2);
	// v2.x = 100;
	// v2.y = 200;
	// line_draw(init->img, &v1, &v2);
	// v2.x = 100;
	// v2.y = 160;
	// line_draw(init->img, &v1, &v2);
	// v2.x = 100;
	// v2.y = 100;
	// line_draw(init->img, &v1, &v2);
	// v2.x = 100;
	// v2.y = 40;
	// line_draw(init->img, &v1, &v2);
	// v2.x = 100;
	// v2.y = 0;
	// line_draw(init->img, &v1, &v2);
	// v2.x = 140;
	// v2.y = 0;
	// line_draw(init->img, &v1, &v2);
	mlx_put_image_to_window(init->mlx, init->data->win_ptr, init->data->img.mlx_img, 0, 0);
	mlx_loop(init->mlx);
	rec_free(arr, 3);
}
