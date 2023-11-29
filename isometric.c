/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:02:42 by dayou             #+#    #+#             */
/*   Updated: 2023/11/29 22:15:08 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	vector_scaling_lst(t_init *init, float *scale)
{
	*scale = get_scale_point(*(t_vector *)(P1), *(t_vector *)(P2),
			*(t_vector *)(P3));
	if (*scale > 30.0f)
		*scale *= 0.6;
	else
		*scale *= 1.2;
	ft_lstiter_arg(init->list, (void *)scale, scale_loop);
}

void	isometric_xyz(t_list *list, float *zratio)
{
	while (list != NULL)
	{
		ft_lstiter_arg(list->content,
			(void *)zratio, xyz_change_isometric_coodinate);
		list = list->next;
	}
}

void	xyz_change_isometric_coodinate(void *content, void *zratio)
{
	t_vector	*point;
	float		x;
	float		y;
	float		z;

	point = content;
	x = point->x;
	y = point->y;
	z = point->z;
	point->x = (COS_30 * (x - y));
	point->y = ((0.5 * (x + y)) - (z * (*(float *)zratio)));
}
