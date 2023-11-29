/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:16:23 by dayou             #+#    #+#             */
/*   Updated: 2023/11/29 21:20:00 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_free(t_init *init)
{
	free(init->data);
	free(init);
}

void	double_lst_free_for_error(t_init *init, char *str)
{
	double_lst_clear(init->list, content_del);
	free(init->data);
	free(init);
	ft_perror(str);
}

void	init_map_arry_free(t_init *init)
{
	rec_free(init->map, 3);
	free(init->data);
	free(init);
}

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
