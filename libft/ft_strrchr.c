/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:59:10 by dayou             #+#    #+#             */
/*   Updated: 2023/04/30 13:38:55 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, int c)
{
	char	character;
	char	*last_chr;
	size_t	i;

	last_chr = NULL;
	i = 0;
	character = (char)c;
	while (str[i])
	{
		if (str[i] == character)
			last_chr = str + i;
		i++;
	}
	if (character == '\0')
		return (str + i);
	return (last_chr);
}
