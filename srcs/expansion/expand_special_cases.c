/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_special_cases.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:28:19 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/26 01:42:22 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	has_outer_quotes(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if (len < 2)
		return (0);
	if (arg[0] == '$' && arg[1] == '"' && arg[len - 1] == '"')
		return (2);
	return ((arg[0] == '"' && arg[len - 1] == '"') || (arg[0] == '\'' && arg[len
			- 1] == '\''));
} */

/* char	*remove_outer_quotes(char *arg)
{
	char	*new_arg;
	size_t	len;

	len = 0;
	new_arg = NULL;
	if (has_outer_quotes(arg))
	{
		len = ft_strlen(arg);
		new_arg = ft_calloc_norm(len - 1, sizeof(char));
		if (new_arg == NULL)
			return (NULL);
		ft_strncpy(new_arg, arg + 1, len - 2);
		new_arg[len - 2] = '\0';
		return (new_arg);
	}
	else if (arg[0] == '$' && has_outer_quotes(arg + 1))
	{
		arg++;
		len = ft_strlen(arg);
		new_arg = ft_calloc_norm(len - 1, sizeof(char));
		if (new_arg == NULL)
			return (NULL);
		ft_strncpy(new_arg, arg + 1, len - 2);
		new_arg[len - 2] = '\0';
		return (new_arg);
	}
	return (ft_strdup(arg));
} */

void	remove_quotes_from_args(t_data *data)
{
	int i;

	i = 0;
	while (data->tokens->args_num != 0 && data->tokens->args[i])
	{
		data->tokens->args[i] = remove_quotes_args(data->tokens->args[i]);
		i++;
	}
}
