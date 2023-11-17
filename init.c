/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:17:49 by dayou             #+#    #+#             */
/*   Updated: 2023/11/18 02:19:31 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./libft/libft.h"

void	ft_perror(const char *str)
{
	int	len;

	len = ft_strlen(str);
	write(2, str, len);
    return exit(1);
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
    const char lf = '\n';
    const char commas = ',';
    t_list * new_node;

    if (fdf_file_open == 0) // 빈 파일이면 fail
        return failed;
    ft_lstiter_arg(init->list, lf, remove_char);
    new_node = ft_lstmap(init->list, ft_split_space, split_del);
    if (new_node == NULL)
        return failed;
    else
    {
        ft_lstclear(init->list, gnl_del);
        init->list = new_node;
    }
    ft_lstiter_arg(init->list, commas, remove_char); //콤마 지우고
    if (lst_true_false_check(init->list, check_non_numeric_char) == failed)
        return failed;
    if (lst_true_false_check(init->list, int_min_max_check) == failed)
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


void remove_char (char * str, char c)
{
    char * tmp;

    tmp = ft_strrchr(str, c);
    *tmp = '\0';
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


void * ft_split_space (void * content)
{
    char ** split;
    t_list * new_list;
    t_list * new_node;
    int i;

/*

list.content = "234234 234987234 -1344";
list->next = node;

list->next->content = "231234 23987 908987";

0x01  -  "234234" (0x01)
        "234967234"
        "-1344"
*/
    split = ft_split((char *)content, ' ');
    if (split == NULL)
        return NULL;
    new_list = NULL;
    i = 0;
    while (split[i])
    {
        new_node = ft_lstnew(split[i]);
        ft_lstadd_back(&new_list, new_node);
        i++;
    }
    split_del(split);
    return new_list;
}


int check_non_numeric_char(void * content)
{
    char ** str;
    int i;
    int j;


    i = 0;
    str = (char **)content; //-\0
    while (str[i])
    {
        j = 0;
        if ((str[i][j] == '-' || str[i][j] == '+'))
            j++;
        while (str[i][j])
        {
            if (!ft_isdigit(str[i][j]))
                return failed;
            j++;
        }
        if (j == 1 && str[i][0] == '-' || str[i][0] == '+')
            return failed;
        i++;
    }
    return success;
}

int int_min_max_check(void * content)
{
    char ** str;
    long long	temp;
    int i;

    str = (char **)content;
    i = 0;

    /*
    list->next      0    1    2    3
    node 0     -   "12" "34" "56" NULL
    node 1
    node 2
    node 3
    
    */
    while (str[i])
    {
        temp = ft_atoi(str[i]);
	    if (temp < INT_MIN || INT_MAX < temp)
		    return (failed);
        i++;
    }
    return (success);
}

int lst_true_false_check (t_list * list, int (*f)(void *))
{
    while (list != NULL)
    {
        if (f(list->content) == failed)
            return failed;
        list = list->next;
    }
    return success;
}


/*
line -> content
while (line = get_next_line())
{
    lst_add_back(line_list, lst_new(line));
}
// remove_endl함수 < 가장 먼저 나타나는 개행문자를 \0로 
lst_iter(line_list, remove_endl);
// 1. 스플릿
cell_list = lst_map(init->list, ft_split(init->list,' '), ft_lstclear); <- 스페이스로 자른 뒤, ',' 나타나는 문자를 \0로 바꿔주기
// 검증
if (lst_every(cel_list, is_valid_word_list) == 0) 숫자 말고 다른 문자가 있는지 체크하기, 인트 민 맥스 체크하기.
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
*/
