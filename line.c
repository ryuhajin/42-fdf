/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:21:35 by dayou             #+#    #+#             */
/*   Updated: 2023/11/28 00:59:13 by dayou            ###   ########.fr       */
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
		dda_to_br(p1, p2, img);
		// point_img_x_plus(v1, v2, img);
	// else
	// 	point_img_y_plus(v1, v2, img);
}

// void point_img_x_plus (t_vector * vec1, t_vector * vec2, t_img * img)
// {
// 	t_vector p1;
// 	t_vector p2;
// 	float slope;
// 	float origin_y;

// 	p1.x = vec1->x;
// 	p2.x = vec2->x;
// 	p1.y = vec1->y;
// 	p2.y = vec2->y;
	
// 	if (p1.x > p2.x)
// 		ft_vector_swap(&p1, &p2);

// 	slope = (float)(p2.y - p1.y) / (float)(p2.x - p1.x) * (p2.x - p1.x);
// 	origin_y = (p1.y + slope / (p2.x - p1.x)) * (p2.x - p1.x);
// 	while (p1.x <= p2.x)
// 	{
// 		img_pix_put(img, p1.x, p1.y);
// 		p1.x += 1.0f;
// 		origin_y += slope / (p2.x - p1.x);
// 		p1.y = roundf(origin_y);
// 	}
// }
// int x1, int y1, int x2, int y2, t_img *img
void dda_to_br(t_point v1, t_point v2, t_img * img)
{
	int delta_y; // 실수 (나눗셈) >> * dx
	int delta_x;
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

// void dda(const int x1, const int y1, const int x2, const int y2)
// {
// 	int px = x1;
// 	int py = y1;
// 	float slope = (y2 - y1) / (x2 - x1); // 실수 (나눗셈) >> * dx
// 	float sum_slope = 0.0f;

// 	while (px <= x2)
// 	{
// 		// draw_point(px, py);
// 		// x
// 		px += 1;
// 		// y
// 		sum_slope += slope;
// 		if (sum_slope > 0.5) // 1/2 (나눗셈) >> * 2
// 		{
// 			sum_slope -= 1.0f;
// 			py += 1;
// 		}
// 	}
// }

// void point_img_y_plus (t_vector * vec1, t_vector * vec2, t_img * img)
// {
// 	return;
// 	t_vector p1;
// 	t_vector p2;
// 	float slope;
// 	float origin_x;

// 	p1.x = vec1->x;
// 	p2.x = vec2->x;
// 	p1.y = vec1->y;
// 	p2.y = vec2->y;

// 	if (p1.y > p2.y)
// 		ft_vector_swap(&p1, &p2);
// 	slope = (float)(p2.x - p1.x) / (float)(p2.y - p1.y);
// 	origin_x = p1.x + slope;
// 	while (p1.y < p2.y - 1.0f)
// 	{
// 		img_pix_put(img, p1.x, p1.y);
// 		p1.y++;
// 		origin_x += slope;
// 		p1.x = roundf(origin_x);
// 	}
// }

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
		printf("vector: %f %f %f\n", vector->x, vector->y, vector->z);
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
        ft_lstclear(&init->list, content_del);
        init->list = new_node;
    }
	ft_lstiter_arg(init->list, (void *)&vector, set_vector_xy);
	ft_lstiter(init->list, print_lst_map);
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

	/* 
	내가 해야할 것
	1. 파싱한 맵을 x,y,z 좌표로 lstmap을 사용하여 vector 만들기
	2. 릭 체크하기
	*/

	/*
	{ A, B }
	basis[0] = A
	basis[1] = B
	{ {COS_30, 0.5}, {-COS_30, 0.5} }
	{COS_30, 0.5}
	basis[0][0] = COS_30 
	(const 자료형) * = (자료형 const)* (자료가 불변이다)
	(자료형) * const (포인터가 불변이다)
	*/
}
