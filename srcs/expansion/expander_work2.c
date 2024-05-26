/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_work.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 23:42:12 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/26 18:39:06 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_fragment(char *arg, int *i)
{
	char	*fragments;

	if (arg[*i] == '"')
		fragments = extract_quoted(arg, i, '"');
	else if (arg[*i] == '\'')
		fragments = extract_quoted(arg, i, '\'');
	else if (arg[*i] == '$')
		fragments = extract_variable(arg, i);
	else
		fragments = extract_regular(arg, i);
	return (fragments);
}
