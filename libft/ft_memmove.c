/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:46:21 by dayou             #+#    #+#             */
/*   Updated: 2023/04/30 13:40:10 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char		*new_dest;
	const unsigned char	*new_src;
	size_t				i;

	new_dest = (unsigned char *)dest;
	new_src = (const unsigned char *)src;
	i = 0;
	if (new_dest == new_src || len == 0)
		return (dest);
	if (new_src > new_dest)
		return (ft_memcpy(dest, src, len));
	else
	{
		while (i < len)
		{
			new_dest[len - 1 - i] = new_src[len - 1 - i];
			i++;
		}
		return ((void *)new_dest);
	}
}
