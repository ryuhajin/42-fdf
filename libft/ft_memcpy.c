/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:11:29 by dayou             #+#    #+#             */
/*   Updated: 2023/05/01 16:52:09 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t num)
{
	size_t				i;
	unsigned char		*new_dest;
	const unsigned char	*new_src;

	new_dest = (unsigned char *)dest;
	new_src = (const unsigned char *)src;
	i = 0;
	if (dest == src || num == 0)
		return (dest);
	while (i < num)
	{
		new_dest[i] = new_src[i];
		i++;
	}
	return (new_dest);
}
