/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:21:35 by dayou             #+#    #+#             */
/*   Updated: 2023/11/29 21:39:20 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_pix_put(t_img *img, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(int *)pixel = WHITE;
}

void	dot_on_pixel(t_img *img, t_vector *v1, t_vector *v2)
{
	float	del_x;
	float	del_y;
	t_point	p1;
	t_point	p2;

	del_x = (float)fabsf(v2->x - v1->x);
	del_y = (float)fabsf(v2->y - v1->y);
	p1.x = roundf(v1->x);
	p1.y = roundf(v1->y);
	p2.x = roundf(v2->x);
	p2.y = roundf(v2->y);
	if (del_x >= del_y)
		x_plus_pixel_put(p1, p2, img);
	else
		y_plus_pixel_put(p1, p2, img);
}

void	x_plus_pixel_put(t_point v1, t_point v2, t_img *img)
{
	int	delta_x;
	int	delta_y;
	int	sum_slope;
	int	unit_y;

	sum_slope = 0;
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
		if (sum_slope * 2 > delta_x)
		{
			sum_slope -= delta_x;
			v1.y += unit_y;
		}
		img_pix_put(img, v1.x, v1.y);
	}
}

void	y_plus_pixel_put(t_point v1, t_point v2, t_img *img)
{
	int	delta_x;
	int	delta_y;
	int	sum_slope;
	int	unit_x;

	sum_slope = 0;
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
		if (sum_slope * 2 > delta_y)
		{
			sum_slope -= delta_y;
			v1.x += unit_x;
		}
		img_pix_put(img, v1.x, v1.y);
	}
}

void	line_draw(t_vector ***arr, t_img *img)
{
	t_idx	index;

	zero_vec(&index);
	while (arr[index.y] != NULL)
	{
		index.x = 0;
		while (arr[index.y][index.x] != NULL)
		{
			if (arr[index.y + 1] != NULL)
			{
				dot_on_pixel(img, arr[index.y][index.x], \
				arr[index.y + 1][index.x]);
			}
			if (arr[index.y][index.x + 1] != NULL)
			{
				dot_on_pixel(img, arr[index.y][index.x], \
				arr[index.y][index.x + 1]);
			}
			index.x++;
		}
		index.y++;
	}
}
