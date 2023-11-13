/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:48:09 by dayou             #+#    #+#             */
/*   Updated: 2023/11/13 23:29:13 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list * head;
	t_list * new_node;
	
	if (lst == NULL)
		return NULL;
	new_node = ft_lstnew(f(lst->content));
	head = new_node;
	if (new_node == NULL || new_node->content == NULL)
	{
		ft_lstclear(&new_node, del);
		return NULL;
	}
	while (lst->next != NULL)
	{
		lst = lst->next;
		new_node = new_node->next;
		new_node = ft_lstnew(f(lst->content));
		if (new_node == NULL || new_node->content == NULL)
		{
			ft_lstclear(&head, del);
			return NULL;
		}
	}
	return (head);
}
