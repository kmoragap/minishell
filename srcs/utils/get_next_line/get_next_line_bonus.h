/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creuther <creuther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:18:34 by creuther          #+#    #+#             */
/*   Updated: 2022/12/26 11:48:47 by creuther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../../../includes/minishell.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_new_base(char *base, int len);
char	*ft_read(char *base, int fd);
int     ft_strlen_nl_end(char *base);
int     ft_strchr_null(char *base, char nl);
size_t	ft_strlen_get(const char *str);
char	*ft_strjoin_get(char *s1, char *s2);
char	*ft_strdup_a(char *src, int len);

#endif
