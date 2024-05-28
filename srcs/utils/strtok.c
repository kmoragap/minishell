/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtok.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:41:49 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/28 14:25:13 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr_after_c(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s + 1);
		++s;
	}
	return (NULL);
}

static size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (ft_strchr(accept, s[i]) == 0)
			break ;
		++i;
	}
	return (i);
}

static char	*ft_strpbrk(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (*s1)
	{
		i = 0;
		while (s2[i])
		{
			if (*s1 == s2[i])
				return ((char *)s1);
			i++;
		}
		s1++;
	}
	return (NULL);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last_token;
	char		*token;

	last_token = NULL;
	if (str == NULL && last_token == NULL)
		return (NULL);
	str += ft_strspn(str, delim);
	if (*str == '\0')
	{
		last_token = NULL;
		return (NULL);
	}
	token = str;
	str = ft_strpbrk(token, delim);
	if (str == NULL)
		last_token = NULL;
	else
	{
		*str = '\0';
		last_token = str + 1;
	}
	return (token);
}
