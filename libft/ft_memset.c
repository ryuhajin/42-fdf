/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:54:11 by dayou             #+#    #+#             */
/*   Updated: 2023/04/30 13:40:15 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t len)
{
	size_t			i;
	unsigned char	c;
	unsigned char	*str;

	i = 0;
	c = (unsigned char)value;
	str = (unsigned char *)ptr;
	while (i < len)
	{
		str[i] = c;
		i++;
	}
	return (str);
}
