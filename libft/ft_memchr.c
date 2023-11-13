/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:02:21 by dayou             #+#    #+#             */
/*   Updated: 2023/04/30 13:39:54 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		character;
	const unsigned char	*char_s;
	size_t				i;

	char_s = (const unsigned char *)s;
	i = 0;
	character = (unsigned char)c;
	while (i < n)
	{
		if (char_s[i] == character)
			return ((void *)char_s + i);
		i++;
	}
	return (NULL);
}
