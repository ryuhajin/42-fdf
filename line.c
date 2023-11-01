/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:21:35 by dayou             #+#    #+#             */
/*   Updated: 2023/11/01 20:46:59 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int line_use_bresenham (int start_x, int start_y, int end_x, int end_y)
{
	// 높이와 가로는 0과 1 사이
	int x = start_x;
	int y = start_y;

	//높이와 가로를 구한다
	int w = end_x - start_x;
	int h = end_y - start_y;

	//직선을 어디다 그을지 초기값 판별식
	int determine = 2 * h - w;
}