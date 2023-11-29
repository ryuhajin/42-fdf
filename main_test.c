/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 20:51:29 by dayou             #+#    #+#             */
/*   Updated: 2023/11/29 23:11:03 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_leak(void)
{
	system("leaks --list -- fdf");
}

int	main(int argc, char *argv[])
{
	t_init	*init;

	atexit(check_leak);
	init = NULL;
	argc_argv_check(argc, argv, &init);
	if (fdf_map_check(init) == failed)
		double_lst_free_for_error(init, "map error\n");
	make_vector_list(init);
	vector_setting_for_render(init);
	line_draw(init->map, init->img);
	mlx_put_image_to_window(init->mlx, init->data->win_ptr,
			init->data->img.mlx_img, 0, 0);
	mlx_key_hook(init->data->win_ptr, close_window, init);
	mlx_hook(init->data->win_ptr, DESTROY_EVENT, 0, close_window_ondestroy,
			init);
	mlx_loop(init->mlx);
	return (0);
}
