/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:03:40 by dayou             #+#    #+#             */
/*   Updated: 2023/04/30 13:40:42 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *str, int c)
{
	char	character;
	size_t	i;

	i = 0;
	character = (char)c;
	while (str[i])
	{
		if (str[i] == character)
			return (str + i);
		i++;
	}
	if (character == '\0')
		return (str + i);
	return (NULL);
}
