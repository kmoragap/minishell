/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:34:26 by creuther          #+#    #+#             */
/*   Updated: 2024/05/19 16:28:02 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_calloc_norm(size_t n, size_t size)
{
	size_t	i;
	void	*arr;

	i = n * size;
	arr = (void *)malloc(i);
	if (arr == NULL)
		return (NULL);
	ft_bzero(arr, i);
	return (arr);
}

void	ft_bzero(void *str, size_t n)
{
	unsigned char	*c;
	size_t			i;

	c = str;
	i = 0;
	while (i < n)
	{
		*c = '\0';
		i++;
		c++;
	}
}

t_token	*move_to_first_token(t_token *token)
{
	while (token->prev)
		token = token->prev;
	return (token);
}

int	ft_strchr(const char *str, int c)
{
	while (c > 127)
		c = c - 128;
	while (*str)
	{
		if (c == *str)
			return (0);
		str++;
	}
	if (c == '\0')
		return (1);
	return (1);
}

char	*ft_strrchr(const char *str, int c)
{
	int i;

	while (c > 127)
		c = c - 128;
	i = 0;
	while (str[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (str[i] == c)
			return ((char *)&str[i]);
		i--;
	}
	return (NULL);
}