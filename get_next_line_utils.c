/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgodoy-m <jgodoy-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:00:32 by jgodoy-m          #+#    #+#             */
/*   Updated: 2025/05/15 16:43:41 by jgodoy-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	append(t_list **list, char *buffer)
{
	t_list	*n_node;
	t_list	*l_node;

	if (!list || !buffer)
		return ;
	n_node = malloc(sizeof(t_list));
	if (!n_node)
	{
		free(buffer);
		return ;
	}
	l_node = ft_lstlast(*list);
	if (!l_node)
		*list = n_node;
	else
		l_node->next = n_node;
	n_node->str = buffer;
	n_node->next = NULL;
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	sizeofline(t_list *list)
{
	int	i;
	int	count;

	if (!list)
		return (0);
	count = 0;
	while (list != NULL)
	{
		i = 0;
		if (!list->str)
			return (0);
		while (list->str[i])
		{
			if (list->str[i] == '\n')
			{
				++count;
				return (count);
			}
			++i;
			++count;
		}
		list = list->next;
	}
	return (count);
}

void	copy_str(t_list *list, char *str)
{
	int	i;
	int	j;

	if (!list || !str)
		return ;
	j = 0;
	while (list != NULL)
	{
		i = 0;
		if (!list->str)
			return ;
		while (list->str[i])
		{
			if (list->str[i] == '\n')
			{
				str[j++] = '\n';
				str[j] = '\0';
				return ;
			}
			str[j++] = list->str[i++];
		}
		list = list->next;
	}
	str[j] = '\0';
}

void	dealloc(t_list **list, t_list *c_node, char *buffer)
{
	t_list	*temp;

	if (!list)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->str);
		free(*list);
		*list = temp;
	}
	*list = NULL;
	if (!c_node)
		return ;
	if (c_node->str && c_node->str[0])
		*list = c_node;
	else
	{
		if (c_node->str != buffer && c_node->str)
			free(c_node->str);
		free(buffer);
		free(c_node);
	}
}
