/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtok2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:41:49 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/26 02:47:26 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strchr_before_c(const char *s, int c)
{
	char	*result;
	int		i;

	i = 0;
	if (s == NULL || c == '\0' || s[0] == '=')
		return (ft_strdup(""));
	while (s[i] != '\0')
	{
		if (s[i] == c)
			break ;
		i++;
	}
	result = (char *)ft_calloc_norm(1, i + 1);
	if (result == NULL)
		return (NULL);
	ft_strncpy(result, s, i);
	result[i] = '\0';
	return (result);
}
