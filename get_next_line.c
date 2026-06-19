/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgodoy-m <jgodoy-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:00:34 by jgodoy-m          #+#    #+#             */
/*   Updated: 2025/05/21 10:32:53 by jgodoy-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(t_list *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		if (!list->str)
			return (0);
		while (list->str[i])
		{
			if (list->str[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

void	create_list(int fd, t_list **list)
{
	char	*buffer;
	ssize_t	bytes;

	while (!found_newline(*list))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
		{
			free(buffer);
			return ;
		}
		buffer[bytes] = '\0';
		append(list, buffer);
	}
}

char	*ft_get_line(t_list *list)
{
	int		size;
	char	*next;

	if (!list)
		return (NULL);
	size = sizeofline(list);
	next = malloc(size + 1);
	if (!next)
		return (NULL);
	copy_str(list, next);
	return (next);
}

void	polish_list(t_list **list)
{
	t_list	*l_node;
	t_list	*c_node;
	int		i;
	int		j;
	char	*buffer;

	if (!list || !*list)
		return ;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return ;
	c_node = malloc(sizeof(t_list));
	if (!c_node)
	{
		free(buffer);
		return ;
	}
	l_node = ft_lstlast(*list);
	if (!l_node || !l_node->str)
	{
		free(buffer);
		free(c_node);
		return ;
	}
	i = 0;
	j = 0;
	while (l_node->str[i] != '\0' && l_node->str[i] != '\n')
		i++;
	if (l_node->str[i] == '\n')
		i++;
	while (l_node->str[i] != '\0')
		buffer[j++] = l_node->str[i++];
	buffer[j] = '\0';
	c_node->str = buffer;
	c_node->next = NULL;
	dealloc(list, c_node, buffer);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, 0, 0) < 0))
		return (NULL);
	create_list(fd, &list);
	if (!list)
		return (NULL);
	line = ft_get_line(list);
	polish_list(&list);
	return (line);
}


