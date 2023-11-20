/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:13:23 by dayou             #+#    #+#             */
/*   Updated: 2023/11/20 20:06:39 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void print_str(void * str)
{
	printf("str:%s ", str);
}

void print_str_lst (void * list)
{
	t_list * node;

	node = (t_list *)list;
	ft_lstiter(list, print_str);
	printf("\n");
}

void lst_print (void * list, void * flag)
{
	t_list * node;
	// char * str;
	int * num;

	node = (t_list *)list;
	if (*(int *)flag == 0)
	{
		ft_lstiter(list, print_str);
		// while (node != NULL)
		// {
		// 	str = (char *)node->content;
		// 	printf("str:%s ", str);
		// 	node = node->next;
		// }
		printf("\n");
	}
	else
	{
		while (node != NULL)
		{
			num = (int *)node->content;
			printf("int:%d ", *num);
			node = node->next;
		}
		printf("\n");
	}
}
