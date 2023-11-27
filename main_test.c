/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 20:51:29 by dayou             #+#    #+#             */
/*   Updated: 2023/11/27 21:09:50 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_idx	* zero_vec(t_idx	*vec)
{
	vec->x = 0;
	vec->y = 0;
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

/*
get array of pointer,
call function for each pointer

arr : array of pointer (data : pointer)
n-dimension (void * int ********)

data : int **
f(int **);
f(void *ptr)
{
	int ** content = ptr;
}

(t_vector *)** arr;
(t_vector *) arr[][];
t_vector arr[][];
t_vector arr[][];
pointer (NULL, unknown(void) type)
arr[0] = 0xa0
arr[1] = 0xb0
arr[2] = NULL

arr[0][0] = 0xa0
arr[0][1] = NULL

arr[0][0]->x = 1

// 1-dimension
printdata(void *ptr); // content를 받아서 int *로 캐스팅 -> 접근해서 출력
{
	(int *)val = ptr;
	printf("%d", *val);
}
(int *)*arr;
ft_arriter(arr, printdata);
// iter의 접근 방식 = 1차원에 content가 있는 방식으로 바라봄
// content가 무언가의 포인터임

// 2-dimension
print1d(void *ptr) // content를 받아서 (int *)*로 캐스팅 -> iter, print1d
{
	(int *)*arr = ptr;
	ft_arriter(arr, printdata);
}
(int *)**arr; // 2차원 데이터
ft_arriter(arr, print1d); // 2차원 데이터를 순회하면서, 1차원 데이터를 출력하는 함수에 넣어라
// iter의 접근 방식 = 1차원에 content가 있는 방식으로 바라봄
print1d(arr[i]);
*/

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

void iso_lst (t_list * list, float zratio)
{
	while (list != NULL)
	{
		ft_lstiter_arg(list->content, (void *)&zratio, xyz_change_isometric_coodinate);
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

	printf("img_width: %f\n", img_width);
	printf("img_height: %f\n", img_height);
	scale = WIDTH / img_width;
	if (scale > HEIGHT / img_height)
		scale = HEIGHT / img_height;
	printf("scale: %f\n", scale);
	return scale;
}

void move_vec (t_vector *** arr)
{
	t_idx	index;

	zero_vec(&index);
	while (arr[index.y] != NULL)
	{
		index.x = 0;
		while (arr[index.y][index.x] != NULL)
		{
			arr[index.y][index.x]->x += 0;
			arr[index.y][index.x]->y += 0;
			index.x++;
		}
		index.y++;
	}
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


int main(int argc, char * argv[])
{
	t_init * init;
	float scale;

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
	scale = get_scale_point(*(t_vector *)(P1), *(t_vector *)(P2), *(t_vector *)(P3));
	ft_lstiter_arg(init->list, (void *)&scale, scale_loop);
	if (scale > 30.0f)
	{
		scale *= 0.6;
		iso_lst(init->list, scale);
	}
	else
		iso_lst(init->list, scale);
	init->map = lst_change_to_arr(init->list);
	draw_line(init->map, init->img);
	// t_vector v1 = {0, 0, 0};
	// t_vector v2 = {1920, 1080, 0};
	// line_draw(init->img, &v1, &v2);
	mlx_put_image_to_window(init->mlx, init->data->win_ptr, init->data->img.mlx_img, 0, 0);
	mlx_loop(init->mlx);
	rec_free(init->map, 3);
}
