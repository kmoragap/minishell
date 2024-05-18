/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creuther <creuther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:43:22 by creuther          #+#    #+#             */
/*   Updated: 2022/12/26 12:05:05 by creuther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin_get(char *s1, char *s2)
{
	char	*new;
	int		a;
	int		b;

	a = -1;
	b = 0;
	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		if (!s1 || !s2)
			return (NULL);
		s1[0] = '\0';
	}
	new = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!new || new == NULL)
		return (NULL);
	while (s1[++a])
		new[a] = s1[a];
	while (s2[b])
		new[a++] = s2[b++];
	new[a] = '\0';
	free(s1);
	return (new);
}

int	ft_strchr_null(char *base, char nl)
{
	if (!base || base == NULL)
		return (0);
	while (*base)
	{
		if (nl == *base)
			return (1);
		base++;
	}
	return (0);
}

char	*ft_new_base(char *base, int len)
{
	char			*newbase;
	unsigned int	a;

	a = 0;
	if (!base[len])
	{
		free(base);
		return (NULL);
	}
	if (base[len] == '\n')
		len++;
	while (base[len + a] != '\0')
		a++;
	newbase = malloc(sizeof(char) * (a + 1));
	if (!newbase)
		return (NULL);
	newbase[a] = '\0';
	while (a--)
		newbase[a] = base[len + a];
	free(base);
	return (newbase);
}

size_t	ft_strlen_get(const char *str)
{
	size_t	i;

	i = 0;
	if (!str || str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}
