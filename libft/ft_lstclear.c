/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:03:24 by dayou             #+#    #+#             */
/*   Updated: 2023/11/13 23:20:23 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*iter;
	t_list *temp;

	if (*lst == NULL)
		return ;
	iter = *lst;
	while (iter != NULL)
	{
		temp = iter;
		iter = iter->next;
		ft_lstdelone(temp, del);
	}
	*lst = NULL;
}
