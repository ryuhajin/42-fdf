/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 22:16:06 by dayou             #+#    #+#             */
/*   Updated: 2023/11/29 22:17:23 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	remove_char(void *str, void *c)
{
	char	*tmp;
	char	find_c;

	find_c = *(char *)c;
	tmp = ft_strrchr((char *)str, find_c);
	if (tmp != NULL)
		*tmp = '\0';
}

void	remove_char_lst(void *list, void *c)
{
	ft_lstiter_arg(list, c, remove_char);
}


long long	atolong(char *str)
{
	long long	numbers;
	int			minus;
	size_t		i;

	numbers = 0;
	minus = 1;
	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if ('-' == str[i] || '+' == str[i])
	{
		if ('-' == str[i])
			minus = -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		numbers *= 10;
		numbers += str[i] - '0';
		i++;
	}
	return (numbers * minus);
}

void	lst_atoi(void *content)
{
	t_list	*list;
	int		*ptr;

	list = (t_list *)content;
	while (list != NULL)
	{
		ptr = (int *)malloc(sizeof(int) * 1);
		*ptr = ft_atoi((char *)list->content);
		free(list->content);
		list->content = (void *)ptr;
		list = list->next;
	}
}
