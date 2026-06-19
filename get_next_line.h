/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgodoy-m <jgodoy-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:00:29 by jgodoy-m          #+#    #+#             */
/*   Updated: 2025/05/15 16:51:41 by jgodoy-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}		t_list;

char	*get_next_line(int fd);
void	polish_list(t_list **list);
char	*ft_get_line(t_list *list);
void	create_list(int fd, t_list **list);
int		found_newline(t_list *list);
void	append(t_list **list, char *buffer);
int		sizeofline(t_list *list);
void	copy_str(t_list *list, char *str);
void	dealloc(t_list **list, t_list *c_node, char *buffer);
t_list	*ft_lstlast(t_list *lst);

#endif