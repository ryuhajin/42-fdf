/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 21:08:20 by dayou             #+#    #+#             */
/*   Updated: 2023/04/30 13:40:53 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	size;
	char	*new_s;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	size = 0;
	size = (s1_len + s2_len);
	new_s = (char *)malloc(sizeof(char) * size + 1);
	if (new_s == NULL)
		return (NULL);
	ft_strlcpy(new_s, s1, s1_len + 1);
	new_s[s1_len] = '\0';
	ft_strlcat(new_s, s2, s1_len + s2_len + 1);
	return (new_s);
}
