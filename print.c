/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:13:23 by dayou             #+#    #+#             */
/*   Updated: 2023/11/24 20:32:03 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void print_str(void * str)
{
	printf("str:%s", str);
}

void print_int(void * num)
{
	printf("%d ", *(int *)num);
}
void print_map(void * map)
{
	t_vector * vector;
	vector = (t_vector *)map;
	printf("{%d %d %d}", vector->x, vector->y, vector->z);
}

void print_lst_in_str (void * list)
{
	ft_lstiter(list, print_str);
	printf("\n");
}

void print_lst_in_int (void * list)
{
	ft_lstiter(list, print_int);
	printf("\n");
}

void print_lst_map (void * list)
{
	ft_lstiter(list, print_map);
	printf("\n");
}
