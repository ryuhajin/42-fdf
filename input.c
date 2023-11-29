/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:51:18 by dayou             #+#    #+#             */
/*   Updated: 2023/11/29 22:29:25 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	newline_check(void *node)
{
	char	*line;

	line = (char *)node;
	if (ft_strlen(line) == 1 && line[0] == '\n')
		return (failed);
	return (success);
}

int	fdf_file_name_check(char *file_name)
{
	int	idx;
	int	result;

	idx = ft_strlen(file_name) - 4;
	result = ft_strncmp(file_name + idx, ".fdf", 4);
	return (result);
}

int	fdf_file_open(t_init *init, char *file_name)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	if (line == NULL)
		return (failed);
	while (line != NULL)
	{
		ft_lstadd_back(&(init->list), ft_lstnew(line));
		line = get_next_line(fd);
	}
	if (lst_true_false_check(init->list, newline_check) == failed)
		return (failed);
	return (success);
}

void	argc_argv_check(int argc, char *argv[], t_init **init)
{
	if (argc != 2)
		ft_perror("error\n");
	if (fdf_file_name_check(argv[1]) != success)
		ft_perror("file error\n");
	if (access(argv[1], R_OK) == failed)
		ft_perror("file error\n");
	*init = all_init();
	if (*init == NULL)
	{
		init_free(*init);
		ft_perror("error\n");
	}
	if (fdf_file_open(*init, argv[1]) == failed)
	{
		ft_lstclear(&(*init)->list, content_del);
		init_free(*init);
		ft_perror("map error\n");
	}
}
