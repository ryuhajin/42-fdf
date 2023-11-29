/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:08:25 by dayou             #+#    #+#             */
/*   Updated: 2023/11/29 22:57:02 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_arriter(void **arr, void (*f)(void *))
{
	unsigned int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		f(arr[i]);
		i++;
	}
}

t_vector	***alloc_map(int y, int x)
{
	t_vector	***ptr;
	int			i;
	int			j;

	i = 0;
	ptr = malloc(sizeof(t_vector **) * (y + 1));
	ptr[y] = NULL;
	while (i < y)
	{
		j = 0;
		ptr[i] = malloc(sizeof(t_vector *) * (x + 1));
		ptr[i][x] = NULL;
		while (j < x)
		{
			ptr[i][j] = malloc(sizeof(t_vector));
			j++;
		}
		i++;
	}
	return (ptr);
}

void	lst_change_to_arr(t_list *lst, t_vector ***map)
{
	t_idx	index;
	t_list	*inner_list;

	zero_vec(&index);
	index.y = 0;
	while (map[index.y] != NULL)
	{
		index.x = 0;
		inner_list = (t_list *)lst->content;
		while (map[index.y][index.x] != NULL)
		{
			map[index.y][index.x]->x = ((t_vector *)inner_list->content)->x;
			map[index.y][index.x]->y = ((t_vector *)inner_list->content)->y;
			map[index.y][index.x]->z = ((t_vector *)inner_list->content)->z;
			inner_list = inner_list->next;
			index.x++;
		}
		lst = lst->next;
		index.y++;
	}
}

void	make_map_arry(t_init *init)
{
	init->map = alloc_map(ft_lstsize(init->list),
			ft_lstsize(init->list->content));
	lst_change_to_arr(init->list, init->map);
	double_lst_clear(init->list, content_del);
}

void	vector_setting_for_render(t_init *init)
{
	float	scale;
	float	s;

	s = 1.5f;
	vector_scaling_lst(init, &scale);
	printf("scale : %f\n", scale);
	if (scale > 20.0f)
		s = 8.0f;
	else
		s = 1.0f;
	isometric_xyz(init->list, &s);
	vector_move_in_window(init);
	make_map_arry(init);
}
