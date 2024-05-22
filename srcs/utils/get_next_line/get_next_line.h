/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:34:26 by creuther          #+#    #+#             */
/*   Updated: 2024/05/21 17:36:56 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

//read
# include <unistd.h>
//malloc, free
# include <stdlib.h>

# ifndef T_LIST
#  define T_LIST

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

# endif

//get_next_line.c
void	free_line(t_list **llist);
char	*read_gnl_line(t_list *llist);
int		line_ends(char *line);
void	save_line(t_list **llist, int fd);
char	*get_next_line(int fd);

void	free_list(t_list **llist, char *new_content);
int		line_length(t_list *llist);
void	ft_lstadd_new(t_list **lst, char *new_content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);

//extra testing functions
// void	print_list(t_list *ll);
// void	print_nl(char *str);

#endif
