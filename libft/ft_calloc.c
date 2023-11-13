/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 21:36:15 by dayou             #+#    #+#             */
/*   Updated: 2023/05/01 16:41:11 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	if (count == 0 || size == 0)
		return (malloc(0));
	if (count > SIZE_T_MAX / size)
		return (NULL);
	mem = (void *)malloc(sizeof(char) * (count * size));
	if (mem == NULL)
		return (NULL);
	ft_bzero(mem, (count * size));
	return (mem);
}
