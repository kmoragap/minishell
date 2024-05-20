/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:35:50 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/18 19:21:59 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*execute_token(t_data *data)
{
	data = piping(data);
	if (data->err_code != ER_NO)
		return (data);
	data = heredoc(data);
	data = create_children(data);
	return (data);
}

void	execute_builtin(t_data *data)
{
	int	type;

	type = check_builtins(data->tokens->cmd);
	if (type == EXPORT)
		execute_export_builtin(data);
	if (type == ENV)
		put_env(data);
	if (type == PWD)
		get_pwd();
	if (type == UNSET)
		ft_unset(data);
	if (type == ECHO)
		ft_echo(data);
	if (type == CD)
		ft_cd(data);
	if (type == EXIT)
		ft_exit(data);
}
