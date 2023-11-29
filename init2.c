/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:29:00 by dayou             #+#    #+#             */
/*   Updated: 2023/11/29 21:23:06 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*make_vector_node(void *list)
{
	t_vector	*vector;
	t_list		*new_list;
	t_list		*new_node;
	t_list		*node;

	new_list = NULL;
	node = (t_list *)list;
	while (node != NULL)
	{
		vector = (t_vector *)malloc(sizeof(t_vector) * 1);
		if (vector == NULL)
			return (NULL);
		vector->z = *(int *)node->content;
		new_node = ft_lstnew(vector);
		if (new_node == NULL)
			return (NULL);
		ft_lstadd_back(&new_list, new_node);
		node = node->next;
	}
	return (new_list);
}

void	set_xy_in_vector_lst(void *list, void *vector)
{
	t_vector	*node_point;
	t_vector	*vec;
	t_list		*temp;

	vec = (t_vector *)vector;
	temp = (t_list *)list;
	vec->x = 0.0f;
	while (temp != NULL)
	{
		node_point = temp->content;
		node_point->x = vec->x;
		node_point->y = vec->y;
		vec->x++;
		temp = temp->next;
	}
	vec->y++;
}

void	make_vector_list(t_init *init)
{
	t_list		*new_node;
	t_vector	vector;

	vector.x = 0.0f;
	vector.y = 0.0f;
	new_node = ft_lstmap(init->list, make_vector_node, content_del);
	if (new_node == NULL)
		double_lst_free_for_error(init, "error\n");
	else
	{
		double_lst_clear(init->list, content_del);
		init->list = new_node;
	}
	ft_lstiter_arg(init->list, (void *)&vector, set_xy_in_vector_lst);
}
