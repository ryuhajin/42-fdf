/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:39:44 by dayou             #+#    #+#             */
/*   Updated: 2023/11/29 22:10:33 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	content_del(void *content)
{
	if (content == NULL)
		return ;
	free(content);
}

void	double_lst_clear(t_list *list, void (*del)(void *))
{
	t_list	*temp;

	if (list == NULL)
		return ;
	while (list != NULL)
	{
		ft_lstclear((t_list **)&list->content, del);
		temp = list;
		list = list->next;
		ft_lstdelone(temp, content_del);
	}
	list = NULL;
}

void	ft_lstiter_arg(t_list *lst, void *arg, void (*f)(void *, void *))
{
	t_list	*temp;

	if (lst == NULL)
		return ;
	temp = lst;
	while (temp != NULL)
	{
		f(temp->content, arg);
		temp = temp->next;
	}
}

int	lst_true_false_check(t_list *list, int (*f)(void *))
{
	while (list != NULL)
	{
		if (f(list->content) == failed)
			return (failed);
		list = list->next;
	}
	return (success);
}
