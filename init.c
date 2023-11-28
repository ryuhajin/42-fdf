/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:17:49 by dayou             #+#    #+#             */
/*   Updated: 2023/11/28 19:29:19 by dayou            ###   ########.fr       */
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

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*iter;
	t_list *temp;

	if (*lst == NULL)
		return ;
	iter = *lst;
	while (iter != NULL)
	{
		temp = iter;
		iter = iter->next;
		ft_lstdelone(temp, del);
	}
	*lst = NULL;
}


void double_lst_clear (t_list * list, void (*del)(void *))
{
	t_list * temp;
	
	if (list == NULL)
		return;
	while (list != NULL)
	{
		ft_lstclear((t_list **)&list->content, del);
		temp = list;
		list = list->next;
		ft_lstdelone(temp, content_del);
	}
	list = NULL;
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
t_init * data_init (t_init * init, t_data * data)
{
	data->mlx_ptr = init->mlx;
	if (data->mlx_ptr == NULL)
		return NULL;
	data->win_ptr = mlx_new_window(init->mlx, WIDTH, HEIGHT, "test");
	if (data->win_ptr == NULL)
		return NULL;
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img.line_length = WIDTH * 4;
	data->img.bits_per_pixel = 32;
	data->img.endian = 0;
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);

	return init;
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
	if (data_init (init, init->data) == NULL)
		return NULL;
    init->img = &(init->data->img);
    init->list = NULL;
	init->map = NULL;
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
        ft_lstclear(&init->list, content_del); // line 지우기
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
	return success;
}
