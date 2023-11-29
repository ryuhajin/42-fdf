/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:17:49 by dayou             #+#    #+#             */
/*   Updated: 2023/11/29 21:22:50 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_init	*data_init(t_init *init, t_data *data)
{
	data->mlx_ptr = init->mlx;
	if (data->mlx_ptr == NULL)
		return (NULL);
	data->win_ptr = mlx_new_window(init->mlx, WIDTH, HEIGHT, "🌷 fdf 🌷");
	if (data->win_ptr == NULL)
		return (NULL);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img.line_length = WIDTH * 4;
	data->img.bits_per_pixel = 32;
	data->img.endian = 0;
	data->img.addr = mlx_get_data_addr(data->img.mlx_img,
			&data->img.bits_per_pixel, &data->img.line_length,
			&data->img.endian);
	return (init);
}

t_init	*all_init(void)
{
	t_init	*init;

	init = malloc(sizeof(t_init) * 1);
	if (init == NULL)
		return (NULL);
	init->mlx = mlx_init();
	if (init->mlx == NULL)
		return (NULL);
	init->data = malloc(sizeof(t_data) * 1);
	if (init->data == NULL)
		return (NULL);
	if (data_init(init, init->data) == NULL)
		return (NULL);
	init->img = &(init->data->img);
	init->list = NULL;
	init->map = NULL;
	return (init);
}
