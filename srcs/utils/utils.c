/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:34:26 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/21 15:28:14 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	f_len(int n)
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
