/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_special_cases.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:28:19 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/26 17:16:08 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes_from_args(t_data *data)
{
	int	i;

	i = 0;
	while (data->tokens->args_num != 0 && data->tokens->args[i])
	{
		data->tokens->args[i] = remove_quotes_args(data->tokens->args[i]);
		i++;
	}
}

char	*expand_variable(char *var, char **env)
{
	char	*expanded;

	expanded = expand_token(var, env);
	if (expanded)
		return (expanded);
	else
		return (ft_strdup(var));
}
