/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 19:52:43 by dayou             #+#    #+#             */
/*   Updated: 2023/04/11 00:19:41 by dayou            ###   ########.fr       */
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

static void	str_maker(long long nbr, char *put_nbr, int i, int minus)
{
	while (i > 0)
	{
		put_nbr[i - 1 + minus] = (nbr % 10) + '0';
		nbr /= 10;
		i--;
	}
}

static void	nb_is_zero(char *putnbr, int fd)
{
	putnbr[0] = '0';
	putnbr[1] = '\0';
	ft_putstr_fd(putnbr, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	char		putnbr[12];
	long long	number;
	int			i;
	int			minus;

	i = 0;
	minus = 0;
	number = (long long)n;
	if (fd < 0)
		return ;
	if (number == 0)
	{
		nb_is_zero(putnbr, fd);
		return ;
	}
	if (number < 0)
	{
		minus = 1;
		number *= -1;
		putnbr[0] = '-';
	}
	i = number_len(number);
	putnbr[i + minus] = '\0';
	str_maker(number, putnbr, i, minus);
	ft_putstr_fd(putnbr, fd);
}
