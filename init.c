/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:17:49 by dayou             #+#    #+#             */
/*   Updated: 2023/11/21 19:14:34 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_perror(const char *str)
{
	int	len;

	len = ft_strlen(str);
	write(2, str, len);
    return exit(1);
}

void	ft_lstiter_arg(t_list *lst,  void * arg, void (*f)(void *, void *))
{
	t_list	*temp;
    

	if (lst == NULL)
		return;
	temp = lst;
	while (temp != NULL)
	{
		f(temp->content, arg);
		temp = temp->next;
	}
}

t_init * all_init (void) // 인자 몇개 들어올지 고정이 아닌것만 동적할당 하기.
{
    t_init * init;

    init = malloc(sizeof(t_init) * 1);
    if (init == NULL)
        return NULL;
    init->mlx = mlx_init(); //mlx는 내가 한게 아니라 프리하면 안됨.
    if (init->mlx == NULL)
        return NULL;
    init->data = malloc(sizeof(t_data) * 1);
    if (init->data == NULL)
        return NULL;
    init->img = &(init->data->img);
    init->list = NULL;

    return init;
}

int fdf_file_open (t_init * init, char * file_name)
{
    int fd;
    char * line;

    fd = open(file_name, O_RDONLY);
    line = get_next_line(fd);
	if (line == NULL)
		return failed;
    while (line != NULL)
    {
        ft_lstadd_back(&(init->list), ft_lstnew(line)); //list가 null이라 첫번째 line이 헤드가 됨.
        line = get_next_line(fd);
    }
    return success;
}

int fdf_map_check (t_init * init, char * file_name)
{
	char * const lf = "\n";
	char * const commas = ",";
	t_list * new_node;

    if (fdf_file_open(init, file_name) == failed) // 빈 파일이면 fail
        return failed;
    ft_lstiter_arg(init->list, (void *)lf, remove_char);
    new_node = ft_lstmap(init->list, ft_split_space, content_del);
    if (new_node == NULL)
        return failed;
    else
    {
        ft_lstclear(&init->list, content_del);
        init->list = new_node;
    }
	if (lst_column_check(init->list) == failed)
		return failed;
    ft_lstiter_arg(init->list, (void *)commas, remove_char_lst); //콤마 지우고
    if (lst_true_false_check(init->list, check_non_numeric_char) == failed)
        return failed;
    if (lst_true_false_check(init->list, int_min_max_check) == failed)
        return failed;
	ft_lstiter(init->list, lst_atoi);
	ft_lstiter(init->list, print_lst_map);
	return success;
}
