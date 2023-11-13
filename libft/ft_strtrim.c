/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:32:12 by dayou             #+#    #+#             */
/*   Updated: 2023/05/11 21:14:09 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_check(unsigned char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = ft_strlen(s1);
	len = j;
	if (s1[0] == 0 && set[0] == 0)
		return (ft_strdup(""));
	while (set_check(s1[i], set) != 0 && i < len)
		i++;
	while (j > 0 && set_check(s1[j - 1], set) != 0)
		j--;
	if (i == 0 && j == len)
		return (ft_strdup(s1));
	if (i >= j)
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * ((j - i) + 1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, &(s1[i]), ((j - i) + 1));
	return (str);
}
