/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:21:35 by dayou             #+#    #+#             */
/*   Updated: 2023/11/26 23:19:32 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void ft_vector_swap (t_vector *a, t_vector *b)
{
	t_vector temp;
	
	temp.x = a->x;
	temp.y = a->y;
	temp.z = a->z;
	a->x = b->x;
	a->y = b->y;
	a->z = b->z;
	b->x = temp.x;
	b->y = temp.y;
	b->z = temp.z;
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
	float slope;

	if (v1->x == v2->x)
		slope = INFINITY;
	else if (v1->y == v2->y)
		slope = 0;
	else
		slope = (float)(v2->y - v1->y) / (float)(v2->x - v1->x);
	if (-1.0f <= slope && slope <= 1.0f) //기울기가 1보다 크다 == 선의 각도가 45도 이상 == y 변화량이 큼 y를 1씩 더해가며 점을 찍어야한다
		point_img_x_plus(v1, v2, img);
	else
		point_img_y_plus(v1, v2, img);
}

void point_img_x_plus (t_vector * vec1, t_vector * vec2, t_img * img)
{
	t_vector p1;
	t_vector p2;
	float slope;
	float origin_y;

	p1.x = vec1->x;
	p2.x = vec2->x;
	p1.y = vec1->y;
	p2.y = vec2->y;
	
	if (p1.x > p2.x)
		ft_vector_swap(&p1, &p2);

	// if (vec1->x == vec2->x)
	// 	slope = 1;
	// else if (vec1->y == vec2->y)
	// 	slope = 0;
	// else
		slope = (float)(p2.y - p1.y) / (float)(p2.x - p1.x);
	origin_y = p1.y;
	while (p1.x <= p2.x)
	{
		// img_pix_put(img, p1.x, p1.y);
		img_pix_put(img, p1.x, origin_y);
		p1.x++;
		origin_y += slope;
		// p1.y = roundf(origin_y);
	}
}

void point_img_y_plus (t_vector * vec1, t_vector * vec2, t_img * img)
{
	t_vector p1;
	t_vector p2;
	float slope;
	float origin_x;

	p1.x = vec1->x;
	p2.x = vec2->x;
	p1.y = vec1->y;
	p2.y = vec2->y;

	if (p1.y > p2.y)
		ft_vector_swap(&p1, &p2);
	slope = (float)(p2.x - p1.x) / (float)(p2.y - p1.y);
	origin_x = p1.x;
	while (p1.y <= p2.y)
	{
		// img_pix_put(img, p1.x, p1.y);
		img_pix_put(img, origin_x, p1.y);
		p1.y++;
		origin_x += slope;
		// p1.x = roundf(origin_x);
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
