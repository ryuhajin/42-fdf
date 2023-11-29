/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:14:13 by dayou             #+#    #+#             */
/*   Updated: 2023/11/29 22:17:21 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*ft_split_space(void *content)
{
	char	**split;
	t_list	*new_list;
	t_list	*new_node;
	int		i;

	split = ft_split((char *)content, ' ');
	if (split == NULL)
		return (NULL);
	new_list = NULL;
	i = 0;
	while (split[i])
	{
		new_node = ft_lstnew(split[i]);
		ft_lstadd_back(&new_list, new_node);
		i++;
	}
	free(split);
	return (new_list);
}

int	check_non_numeric_char(void *list)
{
	t_list	*temp;
	char	*str;
	int		i;

	temp = (t_list *)list;
	while (temp != NULL)
	{
		i = 0;
		str = (char *)temp->content;
		if ((str[i] == '-' || str[i] == '+'))
			i++;
		while (str[i])
		{
			if (!ft_isdigit(str[i]))
				return (failed);
			i++;
		}
		if ((i == 1 && str[0] == '-') || (i == 1 && str[0] == '+'))
			return (failed);
		temp = temp->next;
	}
	return (success);
}

int	int_min_max_check(void *list)
{
	t_list		*temp;
	char		*str;
	long long	atoi;

	temp = (t_list *)list;
	while (temp != NULL)
	{
		str = (char *)temp->content;
		atoi = atolong(str);
		if (atoi < INT_MIN || INT_MAX < atoi)
			return (failed);
		temp = temp->next;
	}
	return (success);
}

int	lst_column_check(t_list *list)
{
	t_list	*node;
	int		lst_cnt;
	int		next_lst_cnt;

	while (list->next != NULL)
	{
		node = list->content;
		lst_cnt = (ft_lstsize(node));
		next_lst_cnt = (ft_lstsize(list->next->content));
		if (lst_cnt != next_lst_cnt)
			return (failed);
		list = list->next;
	}
	return (success);
}

int	fdf_map_check(t_init *init)
{
	char const	*lf = "\n";
	char const	*commas = ",";
	t_list		*new_node;

	ft_lstiter_arg(init->list, (void *)lf, remove_char);
	new_node = ft_lstmap(init->list, ft_split_space, content_del);
	if (new_node == NULL)
		return (failed);
	else
	{
		ft_lstclear(&init->list, content_del);
		init->list = new_node;
	}
	if (lst_column_check(init->list) == failed)
		return (failed);
	ft_lstiter_arg(init->list, (void *)commas, remove_char_lst);
	if (lst_true_false_check(init->list, check_non_numeric_char) == failed)
		return (failed);
	if (lst_true_false_check(init->list, int_min_max_check) == failed)
		return (failed);
	ft_lstiter(init->list, lst_atoi);
	return (success);
}
