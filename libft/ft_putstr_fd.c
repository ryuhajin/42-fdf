/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 16:47:55 by dayou             #+#    #+#             */
/*   Updated: 2023/05/04 14:01:51 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	ssize_t	write_value;
	size_t	str_len;
	size_t	idx;

	str_len = ft_strlen(s);
	idx = 0;
	write_value = 0;
	if (fd < 0)
		return ;
	while (idx < str_len)
	{
		write_value = write(fd, &(s[idx]), (str_len - idx));
		if (write_value == -1)
			return ;
		idx += (size_t)write_value;
	}
}
