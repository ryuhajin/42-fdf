/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:51:18 by dayou             #+#    #+#             */
/*   Updated: 2023/11/13 19:17:41 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int fdf_file_name_check (char * file_name)
{
    int idx;
    int result;

    idx = ft_strlen(file_name) - 4;
    result = ft_strncmp(file_name + idx,  ".fdf", 4);

    return result;
}

int argc_argv_check (int argc, char * argv[])
{
    if (argc != 2)
        return failed;
    if (fdf_file_name_check != success)
        return failed;
    if (access(argv[1], R_OK) == failed)
        return failed;
    return success;
}

