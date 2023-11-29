/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 21:19:44 by dayou             #+#    #+#             */
/*   Updated: 2023/11/29 22:57:49 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clean(t_init *init)
{
	mlx_destroy_image(init->mlx, init->data->img.mlx_img);
	mlx_destroy_window(init->mlx, init->data->win_ptr);
	init_map_arry_free(init);
	exit(0);
}

int	close_window(int key, t_init *init)
{
	if (key == ESC)
		clean(init);
	return (0);
}

int	close_window_ondestroy(t_init *init)
{
	clean(init);
	return (0);
}
