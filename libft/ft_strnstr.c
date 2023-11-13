/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:36:52 by dayou             #+#    #+#             */
/*   Updated: 2023/04/30 13:41:34 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	find_needle(const char *haystack, const char *needle,
		size_t idx, size_t len)
{
	size_t	i;
	size_t	needle_len;

	i = 0;
	needle_len = ft_strlen(needle);
	while (haystack[idx] == needle[i] && i < needle_len && idx < len)
	{
		idx++;
		i++;
	}
	if (needle[i] == 0)
		return (1);
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	idx;
	size_t	same_check;

	i = 0;
	idx = 0;
	same_check = 0;
	if (needle[i] == 0)
		return ((char *)haystack);
	while (haystack[idx] && idx < len)
	{
		if (haystack[idx] == needle[0])
			same_check = (find_needle(haystack, needle, idx, len));
		if (same_check == 1)
			return ((char *)&(haystack[idx]));
		idx++;
	}
	return (NULL);
}
