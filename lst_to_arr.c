/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:02:38 by dayou             #+#    #+#             */
/*   Updated: 2023/11/24 20:25:55 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "fdf.h"

/*
allocate n-dimension memory.
NULL-terminated.
usage: rec_malloc(sizeof(t_vector), (int[]){size_y, size_x}, 2);
*/
void	*rec_malloc(size_t unit, int count[], int depth)
{
	void	**ptr;
	int		idx;

	if (depth == 1)
		return (malloc(unit * (*count)));
	ptr = malloc(sizeof(void *) * (*count + 1));
	ptr[*count] = NULL;
	idx = 0;
	while (idx < *count)
	{
		ptr[idx] = rec_malloc(unit, count + 1, depth - 1);
		idx++;
	}
	return (ptr);
}

/*
free n-dimension memory.
more than 1-dimension pointer sholud be NULL-terminated.
*/
void	rec_free(void *ptr, int depth)
{
	void	**dptr;

	if (depth == 0)
		return ;
	if (depth > 1)
	{
		dptr = ptr;
		while (*dptr != NULL)
		{
			rec_free(*dptr, depth - 1);
			++dptr;
		}
	}
	free(ptr);
}

t_vector	***lst_to_arr(t_list *lst)
{
	t_vector***const	arr
		= rec_malloc(sizeof(t_vector),
			(int []){ft_lstsize(lst), ft_lstsize(lst->content), 1}, 3);
	t_vector			index;
	t_list				*inner_list;

	index.y = 0;
	while (arr[index.y] != NULL)
	{
		index.x = 0;
		inner_list = (t_list *)lst->content;
		while (arr[index.y][index.x] != NULL)
		{
			arr[index.y][index.x]->x = ((t_vector *)inner_list->content)->x;
			arr[index.y][index.x]->y = ((t_vector *)inner_list->content)->y;
			arr[index.y][index.x]->z = ((t_vector *)inner_list->content)->z;
			inner_list = inner_list->next;
			index.x++;
		}
		lst = lst->next;
		index.y++;
	}
	return (arr);
}
