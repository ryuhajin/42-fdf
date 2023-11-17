/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:13:23 by dayou             #+#    #+#             */
/*   Updated: 2023/11/17 23:17:15 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void print_lst (t_init * init)
{
    t_list * temp;
    int i;

    temp = init->list;
    while (temp != NULL)
    {
        int ** map;
        
        map = temp->content;
        while(map[i] != NULL)
        {
            printf("%d ", map);
            i++;
        }
        printf("\n");
    }
}
