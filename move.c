/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:03:50 by dayou             #+#    #+#             */
/*   Updated: 2023/11/29 22:15:37 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_move_x_point(t_vector p1, t_vector p3)
{
	int	move;

	move = fabsf(p3.x);
	move += (WIDTH - fabsf(p1.x - p3.x)) * 0.5;
	return (move);
}

int	get_move_y_point(t_vector p2)
{
	int	move;

	move = (HEIGHT - fabsf(p2.y)) * 0.5;
	return (abs(move));
}

void	move_xy(void *pvec, void *arg)
{
	t_vector	*vec;
	t_point		*move_xy;

	vec = pvec;
	move_xy = arg;
	vec->x += move_xy->x;
	vec->y += move_xy->y;
}

void	move_loop(void *lst, void *arg)
{
	t_list	*list;

	list = lst;
	ft_lstiter_arg(list, arg, move_xy);
}

void	vector_move_in_window(t_init *init)
{
	t_point		move_xy;
	t_vector	p1;
	t_vector	p2;
	t_vector	p3;

	p1 = *(t_vector *)ft_lstlast(init->list->content)->content;
	p2 = *(t_vector *)ft_lstlast(ft_lstlast(init->list)->content)->content;
	p3 = *(t_vector *)((t_list *)ft_lstlast(init->list)->content)->content;
	move_xy.x = get_move_x_point(p1, p3);
	move_xy.y = get_move_y_point(p2);
	ft_lstiter_arg(init->list, (void *)&move_xy, move_loop);
}
