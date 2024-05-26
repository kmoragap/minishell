/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:34:26 by creuther          #+#    #+#             */
/*   Updated: 2024/05/25 16:57:04 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_itoa(int n)
{
	int		len;
	int		num;
	char	*s;

	len = f_len(n);
	num = n;
	s = (char *)ft_calloc_norm(1, (sizeof(char) * len) + 1);
	if (s == NULL)
		return (NULL);
	s[len] = '\0';
	if (num == 0)
		s[0] = '0';
	if (num < 0)
	{
		s[0] = '-';
		num = -num;
	}
	while (num)
	{
		s[--len] = num % 10 + '0';
		num /= 10;
	}
	return (s);
}
