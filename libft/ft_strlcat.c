/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:57:21 by dayou             #+#    #+#             */
/*   Updated: 2023/05/01 16:51:20 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	idx;
	size_t	i;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	idx = 0;
	i = 0;
	if (size < dest_len)
		return (src_len + size);
	while (dest[i])
		i++;
	while (src[idx] && i + 1 < size)
	{
		dest[i] = src[idx];
		i++;
		idx++;
	}
	dest[i] = '\0';
	return (dest_len + src_len);
}
