/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:21:35 by dayou             #+#    #+#             */
/*   Updated: 2023/11/28 20:21:20 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void ft_vector_swap (t_point *a, t_point *b)
{
	t_point temp;
	
	temp.x = a->x;
	temp.y = a->y;
	a->x = b->x;
	a->y = b->y;
	b->x = temp.x;
	b->y = temp.y;
}

int get_move_x_point (t_vector p1, t_vector p3)
{
	int move;
	
	move = fabsf(p3.x);
	move += (WIDTH - fabsf(p1.x - p3.x)) * 0.5;
	printf("p1.x : %f p3.x: %f\n", p1.x, p3.x);
	printf("move: %d\n", move);
	return (move);
}

int get_move_y_point (t_vector p2)
{
	int move;
	
	move = (HEIGHT - fabsf(p2.y)) * 0.5;
	return abs(move);
}


void img_pix_put (t_img * img, int x, int y)
{
	// !DEBUG
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	char * pixel;
	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	//0,0에서 시작한 포인터를 x,y만큼 움직이기
	*(int *)pixel = WHITE; // 좌표만큼 도화지를 움직인 후 해당 좌표에 점 찍기 (컬러를 넣어서)
}

void line_draw(t_img * img, t_vector *v1, t_vector *v2)
{
	float del_x;
	float del_y;
	t_point p1;
	t_point p2;

	del_x = (float)fabsf(v2->x - v1->x);
	del_y = (float)fabsf(v2->y - v1->y);
	p1.x = roundf(v1->x);
	p1.y = roundf(v1->y);
	p2.x = roundf(v2->x);
	p2.y = roundf(v2->y);
	if (del_x > del_y)
		x_plus_pixel_put(p1, p2, img);
	else
		y_plus_pixel_put(p1, p2, img);
}


void x_plus_pixel_put(t_point v1, t_point v2, t_img * img)
{
	int delta_x;
	int delta_y; // 실수 (나눗셈) >> * dx
	int sum_slope = 0;
	int	unit_y;

	if (v1.x > v2.x)
		ft_vector_swap(&v1, &v2);
	unit_y = 1;
	if (v1.y > v2.y)
		unit_y = -1;
	delta_y = abs(v2.y - v1.y);
	delta_x = abs(v2.x - v1.x);
	while (v1.x < v2.x)
	{
		v1.x += 1;
		sum_slope += delta_y;
		if (sum_slope * 2 > delta_x) // 1/2 (나눗셈) >> * 2
		{
			sum_slope -= delta_x;
			v1.y += unit_y;
		}
		img_pix_put(img, v1.x, v1.y);
	}
}

void y_plus_pixel_put(t_point v1, t_point v2, t_img * img)
{
	int delta_x; // 실수 (나눗셈) >> * dx
	int delta_y;
	int sum_slope = 0;
	int	unit_x;

	if (v1.y > v2.y)
		ft_vector_swap(&v1, &v2);
	unit_x = 1;
	if (v1.x > v2.x)
		unit_x = -1;
	delta_y = abs(v2.y - v1.y);
	delta_x = abs(v2.x - v1.x);
	while (v1.y < v2.y)
	{
		v1.y += 1;
		sum_slope += delta_x;
		if (sum_slope * 2 > delta_y) // 1/2 (나눗셈) >> * 2
		{
			sum_slope -= delta_y;
			v1.x += unit_x;
		}
		img_pix_put(img, v1.x, v1.y);
	}
}

void * make_vector_node (void * list) //map에서 list->content를 넘겨준다. (즉 list 행을 넘겨줌)
{
	t_vector * vector;
	t_list * new_list;
	t_list * new_node;
	t_list * node;
	
	new_list = NULL;
	node = (t_list *)list;
	while (node != NULL)
	{
		vector = (t_vector *)malloc(sizeof(t_vector) * 1);
		if (vector == NULL)
			return NULL;
		vector->z = *(int *)node->content;
		new_node = ft_lstnew(vector);
		if (new_node == NULL)
			return NULL;
		ft_lstadd_back(&new_list, new_node);
		node = node->next;
	}
	return new_list;
}

void set_vector_xy (void * list, void * vector)
{
	t_vector * node_point;
	t_vector * vec;
	t_list * temp;

	vec = (t_vector *)vector;
	temp = (t_list *)list;
	vec->x = 0.0f;
	while (temp != NULL)
	{
		node_point = temp->content;
		node_point->x = vec->x;
		node_point->y = vec->y;
		vec->x++;
		temp = temp->next;
	}
	vec->y++;
}

int make_vector_list(t_init * init)
{
	t_list * new_node;
	t_vector vector;
	
	vector.x = 0.0f;
	vector.y = 0.0f;
	new_node = ft_lstmap(init->list, make_vector_node, content_del);
    if (new_node == NULL)
        return failed;
    else
    {
        double_lst_clear(init->list, content_del);
        init->list = new_node;
    }
	ft_lstiter_arg(init->list, (void *)&vector, set_vector_xy);
	return success;
}

void xyz_change_isometric_coodinate (void * content, void * zratio) 
{
	t_vector * const point = content;
	const float x = point->x;
	const float y = point->y;
	const float z = point->z;
	const float ratio = *(float *)zratio;

	point->x = (COS_30 * (x - y));
	point->y = ((0.5 * (x + y)) - (z * ratio));
}
