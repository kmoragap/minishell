/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:34:26 by kmoraga           #+#    #+#             */
/*   Updated: 2024/04/19 17:48:58 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isascii(int c)
{
	return ((c >= 0 && c <= 127));
}

int	ft_isdigit(int c)
{
	return ((c >= 48 && c <= 57));
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	else
		return (0);
}



static int	f_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		len++;
		n = -n;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}


char	*ft_itoa(int n)
{
	int		len;
	int		num;
	char	*s;

	len = f_len(n);
	num = n;
	s = (char *)malloc((sizeof(char) * len) + 1);
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
