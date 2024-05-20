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

char	*ft_strnjoin(char *s1, char *s2, int len2)
{
	char	*new;
	size_t	len;

	len = ft_strlen((char *)s1) + len2;
	new = (char *)malloc(len + 1);
	if (new == NULL)
		return (NULL);
	ft_memcpy((void *)new, (const void *)s1, ft_strlen((char *)s1));
	ft_memmove((void *)(new + ft_strlen((char *)s1)), (const void *)s2, len2);
	new[len] = '\0';
	free(s1);
	return (new);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	len;

	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	new = (char *)malloc(len + 1);
	if (new == NULL)
		return (NULL);
	ft_memcpy((void *)new, (const void *)s1, ft_strlen((char *)s1));
	ft_memmove((void *)(new + ft_strlen((char *)s1)), (const void *)s2,
		ft_strlen((char *)s2));
	new[len] = '\0';
	return (new);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*s;
	char		*d;
	size_t		i;

	i = 0;
	d = dest;
	s = src;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		*d = *s;
		s++;
		d++;
		i++;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*s;
	char		*d;
	size_t		i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	d = dest;
	s = src;
	while (i < n)
	{
		if (s < d)
			d[n - 1 - i] = s[n - 1 - i];
		else
			d[i] = s[i];
		i++;
	}
	return (dest);
}

int	is_valid_expand_var(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
