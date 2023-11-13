/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:30:41 by dayou             #+#    #+#             */
/*   Updated: 2023/11/13 19:30:58 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*ft_strdup_gnl(char *s1)
{
	char	*line;
	size_t	size;
	size_t	idx;

	size = 0;
	while (s1[size])
		size++;
	line = (char *)malloc(sizeof(char) * (size + 1));
	if (line == NULL)
		return (NULL);
	idx = 0;
	while (s1[idx])
	{
		line[idx] = s1[idx];
		idx++;
	}
	line[size] = '\0';
	return (line);
}

char	*ft_strjoin_gnl(char *s1, char *s2, ssize_t size)
{
	ssize_t	len;
	ssize_t	idx;
	char	*line;

	len = 0;
	while (s1[len])
		len++;
	line = (char *)malloc(sizeof(char) * (len + size) + 1);
	if (line == NULL)
	{
		free(s1);
		return (NULL);
	}
	line[len + size] = '\0';
	ft_strlcpy_gnl(line, s1);
	idx = 0;
	while (idx < size)
	{
		line[len + idx] = s2[idx];
		idx++;
	}
	free(s1);
	return (line);
}

size_t	ft_strlcpy_gnl(char *dest, char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (i);
}

ssize_t	find_newline(char *buff, ssize_t *size)
{
	ssize_t	idx;

	idx = 0;
	while (buff[idx])
	{
		if (buff[idx] == '\n')
		{
			*size = idx;
			return (make_new_line);
		}
		idx++;
	}
	*size = idx;
	return (no_new_line);
}
