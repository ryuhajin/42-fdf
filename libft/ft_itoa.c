/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:15:35 by dayou             #+#    #+#             */
/*   Updated: 2023/04/30 13:39:41 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	number_len(long long nbr)
{
	int	cnt;

	cnt = 0;
	while (nbr > 0)
	{
		nbr /= 10;
		cnt++;
	}
	return (cnt);
}

static void	str_maker(long long nbr, char *itoa_str, int size, int minus)
{
	while (size > 0)
	{
		itoa_str[size - 1 + minus] = (nbr % 10) + '0';
		nbr /= 10;
		size--;
	}
}

char	*ft_itoa(int n)
{
	long long	number;
	int			minus;
	int			size;
	char		*itoa_str;

	number = 0;
	minus = 0;
	size = 0;
	number = (long long)n;
	if (number == 0)
		return (ft_strdup("0"));
	if (number < 0)
	{
		minus = 1;
		number *= -1;
	}
	size = number_len(number);
	itoa_str = (char *)malloc(sizeof(char) * (minus + size + 1));
	if (!itoa_str)
		return (NULL);
	itoa_str[minus + size] = '\0';
	if (minus)
		itoa_str[0] = '-';
	str_maker(number, itoa_str, size, minus);
	return (itoa_str);
}
