/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:21:35 by dayou             #+#    #+#             */
/*   Updated: 2023/11/23 20:47:03 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void img_pix_put (t_img * img, int x, int y, int color)
{
	char * pixel;
	//line_length = width * 4 (가로 길이 * int 4byte)
	//bit_per_pixel = pixel bit == 32 (int 4byte)
	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	//0,0에서 시작한 포인터를 x,y만큼 움직이기
	*(int *)pixel = color; // 좌표만큼 도화지를 움직인 후 해당 좌표에 점 찍기 (컬러를 넣어서)
}

void line_draw (int x1, int y1, int x2, int y2, t_img * img, int color)
{
	float delta_x = x2 - x1; //x 변화량
	float delta_y = y2 - y1; //y 변화량
	float slope;
	float origin_y1;
	slope = delta_y / delta_x;
	origin_y1 = y1;
	while(x1 <= x2) // x1이 x2보다 작을수도 있다 <- 이 경우 생각하기
	{
		img_pix_put(img, x1, y1, color);
		x1++;
		origin_y1 += slope;
		y1 = roundf(origin_y1);
	}
}

void xyz_change_isometric_coodinate (void * content, void * pfilter)
{
	t_vector*const point = content;
	const float x = point->x;
	const float y = point->y;
	const float z = point->z;
	const float filter = *(float *)pfilter;

	point->x = roundf(COS_30 * (x - y));
	point->y = roundf((0.5 * (x + y)) - (z * filter));

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
