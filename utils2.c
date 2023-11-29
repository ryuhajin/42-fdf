/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:47:25 by dayou             #+#    #+#             */
/*   Updated: 2023/11/29 21:15:36 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_idx	*zero_vec(t_idx *vec)
{
	vec->x = 0;
	vec->y = 0;
	return (vec);
}

void	ft_vector_swap(t_point *a, t_point *b)
{
	t_point	temp;

	temp.x = a->x;
	temp.y = a->y;
	a->x = b->x;
	a->y = b->y;
	b->x = temp.x;
	b->y = temp.y;
}

void	ft_perror(const char *str)
{
	int	len;

	len = ft_strlen(str);
	write(2, str, len);
	return (exit(1));
}
