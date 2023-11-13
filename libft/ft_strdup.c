/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:11:41 by dayou             #+#    #+#             */
/*   Updated: 2023/04/14 20:25:27 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*s1_is_null(void)
{
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * 1);
	if (new_str == NULL)
		return (NULL);
	new_str[0] = '\0';
	return (new_str);
}

char	*ft_strdup(const char *s1)
{
	char	*new_str;
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	if (s1[0] == '\0')
		return (s1_is_null());
	size = ft_strlen(s1);
	new_str = (char *)malloc(sizeof(char) * (size + 1));
	if (new_str == NULL)
		return (NULL);
	while (s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	new_str[size] = '\0';
	return (new_str);
}
