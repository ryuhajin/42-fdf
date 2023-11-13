/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:17:49 by dayou             #+#    #+#             */
/*   Updated: 2023/11/14 00:50:58 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./libft/libft.h"

void	ft_perror(const char *str)
{
	int	len;

	len = ft_strlen(str);
	write(2, str, len);
    return exit(1)
}

t_init * all_init (void) // 인자 몇개 들어올지 고정이 아닌것만 동적할당 하기.
{
    t_init * init;

    init = malloc(sizeof(t_init) * 1);
    if (init == NULL)
        return failed;
    init->mlx = mlx_init(); //mlx는 내가 한게 아니라 프리하면 안됨.
    if (init->mlx == NULL)
        return failed;
    init->data = malloc(sizeof(t_data) * 1);
    if (init->data == NULL)
        return failed;
    init->img = &(init->data->img);
    init->list = NULL;

    return init;
}

int list_init (t_init * init, char * file_name)
{
    if (fdf_file_open == 0)
        return failed;
}

int fdf_file_open (t_init * init, char * file_name)
{
    int fd;
    int EOF_flag;
    char * line;

    EOF_flag = 0;
    fd = open(file_name, O_RDONLY);
    line = get_next_line(fd);
    while (line != NULL)
    {
        EOF_flag = 1;
        ft_lstadd_back(&(init->list), ft_lstnew(line));
        line = get_next_line(fd);
    }
    return EOF_flag;
}

void gnl_del (void * content)
{
    free(content);
}

void split_del (void * content)
{
    char ** split;
    int i;

    i = 0;
    split = (char **)content;

    while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void remove_lf (char * str)
{
    char * tmp;

    tmp = ft_strrchr(str, '\n');
    *tmp = '\0';
}

void * ft_split_space (void * ptr)
{
    char ** split;
    split = ft_split(ptr, ' ');
    if (split == NULL)
        return NULL;

    return (void *)split;
}

void * split_use_lstmap (t_init * init)
{
    t_list * new_list;
    
    new_list = ft_lstmap(init->list, ft_split_space, split_del);
    if (new_list == NULL)
        return NULL;
    ft_lstclear(init->list, gnl_del);
    
    return new_list;
}


/*
line -> content
while (line = get_next_line())
{
    lst_add_back(line_list, lst_new(line));
}
// remove_endl함수 < 가장 먼저 나타나는 개행문자를 
lst_iter(line_list, remove_endl);
// 1. 스플릿
cell_list = lst_map(init->list, ft_split(init->list,' '), ft_lstclear); <- 
// 검증
if (lst_every(cel_list, is_valid_word_list) == 0)
{
    // free
    return (NULL);
}
// 2. atoi
numeric_list = lst_map(cell_list, atoi);
lst_clear(cell_list, free);
lst_clear(line_list, free);
return numeric_list;

is_valid_word_form(char *word)
{
    // 각 단어별로 형식이 맞는지 체크
    // 123
    // 123,0xff
    // return 1
    // ++123
    // return 0
}

is_valid_word_list(t_list *word_lst)
{
    return lst_every(word_lst, is_valid_word_form)
}
*/