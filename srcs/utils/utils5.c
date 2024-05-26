/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:34:26 by creuther          #+#    #+#             */
/*   Updated: 2024/05/26 19:33:45 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *src)
{
	char	*dest;

	if(!src)
		return (NULL);
	dest = (char *)ft_calloc_norm(1, ft_strlen((char *)src) + 1);
	if (!dest)
		return (NULL);
	dest = ft_strcpy((char *)src, dest);
	return (dest);
}

char	*ft_strndup(char *src, int len)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	while (i < len && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcpy(char *src, char *dest)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_calloc(t_data *data, t_free code, void **arr, size_t size)
{
	*arr = ft_calloc_norm(1, size);
	if (!(*arr))
	{
		*arr = NULL;
		malloc_error(data, code);
		return (1);
	}
	ft_bzero(*arr, size);
	return (0);
}
