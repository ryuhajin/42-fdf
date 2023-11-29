/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:48:09 by dayou             #+#    #+#             */
/*   Updated: 2023/11/29 21:16:06 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	dummy_node;
	t_list	*iter;

	iter = &dummy_node;
	if (lst == NULL)
		return (NULL);
	while (lst != NULL)
	{
		iter->next = ft_lstnew(f(lst->content));
		if (iter->next == NULL || iter->next->content == NULL)
		{
			ft_lstclear(&iter->next, del);
			return (NULL);
		}
		iter = iter->next;
		lst = lst->next;
	}
	return (dummy_node.next);
}
