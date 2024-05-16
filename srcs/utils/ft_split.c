/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creuther <creuther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:39:52 by creuther          #+#    #+#             */
/*   Updated: 2024/05/10 16:32:13 by creuther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cnum(char *s, char c)
{
	int	is;

	is = 0;
	while (s[is])
	{
		if (s[is] == c || s[is] == '\0')
			return (is);
		is++;
	}
	return (is);
}

int	ft_num(char *s, char c)
{
	int	is;
	int	j;
	int	x;

	is = 0;
	j = 0;
	while (s[is])
	{
		x = 0;
		while (s[is] == c && s[is])
			is++;
		while (s[is] != c && s[is])
		{
			is++;
			x = 1;
		}
		if (x == 1)
			j++;
	}
	return (j);
}

char	**ft_malloc(char const *s, char c)
{
	char	**ss;
	int		is;
	int		j;

	ss = malloc((ft_num((char *)s, c) + 1) * sizeof(char *));
	if (ss == NULL)
		return (NULL);
	is = -1;
	j = 0;
	while (s[++is])
	{
		if (s[is] != c)
		{
			ss[j] = malloc((ft_cnum((char *)s + is, c) + 1)
					* sizeof(char));
			if (ss[j++] == NULL)
				return (NULL);
			while (s[is] != c && s[is] != '\0')
				is++;
		}
		if (s[is] == '\0')
			break ;
	}
	ss[j] = 0;
	return (ss);
}

char	**ft_most_work(char const *s, char c, size_t is, size_t j)
{
	char	**ss;
	size_t	i;

	ss = ft_malloc(s, c);
	if (!ss)
		return (NULL);
	while (s[++is])
	{
		if (s[is] != c)
		{
			i = 0;
			while (s[is] != c && s[is] != '\0')
			{
				ss[j][i++] = s[is++];
				if (s[is] == c || s[is] == '\0')
					ss[j][i] = '\0';
			}
			j++;
		}
		if (s[is] == '\0')
			break ;
	}
	return (ss);
}

char	**ft_split(char const *s, char c)
{
	char	**ss;
	size_t	is;
	size_t	j;

	is = -1;
	j = 0;
	if (!s)
		return (NULL);
	ss = ft_most_work(s, c, is, j);
	if (!ss)
		return (NULL);
	return (ss);
}
