/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 22:13:49 by dayou             #+#    #+#             */
/*   Updated: 2023/11/29 22:15:17 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	xy_scale_change(void *pvec, void *arg)
{
	t_vector	*vec;
	float		*scale;

	vec = pvec;
	scale = arg;
	vec->x *= *scale;
	vec->y *= *scale;
}

void	scale_loop(void *plst, void *arg)
{
	t_list	*lst;

	lst = plst;
	ft_lstiter_arg(lst, arg, xy_scale_change);
}

float	get_scale_point(t_vector p1, t_vector p2, t_vector p3)
{
	float	scale;
	float	img_width;
	float	img_height;
	float	zratio;

	zratio = 0.0f;
	xyz_change_isometric_coodinate((void *)&p1, (void *)&zratio);
	xyz_change_isometric_coodinate((void *)&p2, (void *)&zratio);
	xyz_change_isometric_coodinate((void *)&p3, (void *)&zratio);
	img_width = fabsf(p1.x - p3.x);
	img_height = fabsf(p2.y);
	scale = WIDTH / img_width;
	if (scale > HEIGHT / img_height)
		scale = HEIGHT / img_height;
	return (scale * 0.6);
}
