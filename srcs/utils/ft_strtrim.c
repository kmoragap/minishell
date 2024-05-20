/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creuther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:56:12 by creuther          #+#    #+#             */
/*   Updated: 2022/10/19 14:59:39 by creuther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static size_t	ft_check(char const *s1, char const *set)
{
	if ((!s1 && !set) || !s1 || *s1 == '\0')
		return (0);
	else
		return (1);
}

static size_t	ft_start(char const *s1, char const *set)
{
	size_t	is1start;
	size_t	isset;
	size_t	is1end;

	is1end = ft_strlen((char *)s1) - 1;
	is1start = 0;
	isset = 0;
	while (is1start <= is1end)
	{
		if (s1[is1start] != set[isset] && set[isset])
			isset++;
		else if (s1[is1start] == set[isset] && set[isset])
		{
			is1start++;
			isset = 0;
		}
		else if (!set[isset])
			break ;
	}
	return (is1start);
}

static size_t	ft_end(char const *s1, char const *set, size_t is1start)
{
	size_t	isset;
	size_t	is1end;

	is1end = ft_strlen((char *)s1) - 1;
	isset = 0;
	while (is1end >= is1start)
	{
		if (s1[is1end] != set[isset] && set[isset])
			isset++;
		else if (s1[is1end] == set[isset] && set[isset])
		{
			is1end--;
			isset = 0;
		}
		else if (!set[isset])
			break ;
	}
	return (is1end);
} */

/* char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	size_t	is1start;
	size_t	is1end;

	if (ft_check(s1, set) == 0 || ft_start(s1, set) == (size_t)ft_strlen(s1) - 1)
	{
		new = malloc(sizeof(char) * 1);
		if (!new)
			return (NULL);
		*new = '\0';
		return (new);
	}	
	is1start = ft_start(s1, set);
	is1end = ft_end(s1, set, is1start);
	new = malloc(sizeof(char) * (is1end - is1start + 2));
	if (!new)
		return (NULL);
	ft_memcpy((void *)new,
		(const void *)(s1 + is1start), is1end - is1start + 1);
	new[is1end - is1start + 1] = '\0';
	return (new);
} */

static int	isinset(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_Kstrncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
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

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	first;
	size_t	last;

	if (!s1)
		return (0);
	first = 0;
	while (s1[first] && isinset(s1[first], set))
		first++;
	if (!s1[first])
	{
		res = malloc(1);
		res[0] = '\0';
		return (res);
	}
	last = ft_strlen(s1) - 1;
	while (s1[last] && isinset(s1[last], set))
		last--;
	res = malloc((last - first + 2) * sizeof(char));
	if (!res)
		return (0);
	ft_Kstrncpy(res, &s1[first], (last - first + 1));
	res[last - first + 1] = '\0';
	return (res);
}