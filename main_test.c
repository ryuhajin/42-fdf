/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 20:51:29 by dayou             #+#    #+#             */
/*   Updated: 2023/11/20 19:30:35 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int argc, char * argv[])
{
	t_init * init;
	
	if (argc_argv_check (argc, argv) == failed)
	{
		printf("argc argv error\n");
		return 0;
	}
	init = first_init();
	if (init == NULL)
	{
		printf("init error\n");
		return 0;
	}
	if (list_init (init, argv[1]) == failed)
	{
		printf("input error\n");
		return 0;
	}
}
