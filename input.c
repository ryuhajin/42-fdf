/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:51:18 by dayou             #+#    #+#             */
/*   Updated: 2023/11/20 14:34:19 by dayou            ###   ########.fr       */
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
    if (fdf_file_name_check(argv[1]) != success) //파일명이 *.fdf 인지 체크
        return failed;
    if (access(argv[1], R_OK) == failed) //파일 권한이 있는지 체크
        return failed;
    return success;
}

