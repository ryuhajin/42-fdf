/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:21:35 by dayou             #+#    #+#             */
/*   Updated: 2023/11/13 13:26:39 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
