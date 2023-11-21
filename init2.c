/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:14:13 by dayou             #+#    #+#             */
/*   Updated: 2023/11/21 20:00:14 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void content_del (void * content)
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

void remove_char (void * str, void * c)
{
    char * tmp;
	char find_c;

	find_c = *(char *)c;
    tmp = ft_strrchr((char *)str, find_c);
	if (tmp != NULL)
    	*tmp = '\0';
}

void remove_char_lst (void * list, void * c)
{
	ft_lstiter_arg(list, c, remove_char);
}

long long atolong (char * str)
{
	long long	numbers;
	int			minus;
	size_t		i;

	numbers = 0;
	minus = 1;
	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if ('-' == str[i] || '+' == str[i])
	{
		if ('-' == str[i])
			minus = -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		numbers *= 10;
		numbers += str[i] - '0';
		i++;
	}
	return (numbers * minus);
}

void * ft_split_space (void * content)
{
    char ** split;
    t_list * new_list;
    t_list * new_node;
    int i;

    split = ft_split((char *)content, ' ');
    if (split == NULL)
        return NULL;
    new_list = NULL;
    i = 0; 
    while (split[i])
    {
        new_node = ft_lstnew(split[i]); //split으로 잘린 word를 하나하나 노드화
        ft_lstadd_back(&new_list, new_node);
        i++;
    }
	free(split);
    return new_list;
}


int check_non_numeric_char(void * list)
{
	t_list * temp;
    char * str;
    int i;
	
	temp = (t_list *)list;
    while (temp != NULL)
    {	
		i = 0;
		str = (char *)temp->content;
        if ((str[i] == '-' || str[i] == '+'))
			i++;
        while (str[i])
        {
            if (!ft_isdigit(str[i]))
                return failed;
			i++;
        }
        if ((i == 1 && str[0] == '-') || (i == 1 && str[0] == '+'))
            return failed;
		temp = temp->next;
    }
    return success;
}

int int_min_max_check(void * list)
{
	t_list * temp;
    char * str;
    long long	atoi;

	temp = (t_list *)list;
	while (temp != NULL)
	{
		str = (char *)temp->content;
		atoi = atolong(str);
		if (atoi < INT_MIN || INT_MAX < atoi)
			return (failed);
		temp = temp->next;
	}
    return (success);
}

void lst_atoi (void * content)
{
	t_list * list;
	int * ptr;

	list = (t_list *)content;
	
	while (list != NULL)
	{
		ptr = (int *)malloc(sizeof(int) * 1);
		*ptr = ft_atoi((char *)list->content);
		free(list->content);
		list->content = (void *)ptr;
		list = list->next;
	}
}

int lst_column_check (t_list * list)
{
	t_list * node;
	int lst_cnt;
	int next_lst_cnt;

	while (list->next != NULL)
	{
		node = list->content;
		lst_cnt = (ft_lstsize(node));
		next_lst_cnt = (ft_lstsize(list->next->content));
		if (lst_cnt != next_lst_cnt)
			return failed;
		list = list->next;
	}
	return success;
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
