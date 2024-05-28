/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 12:15:14 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/28 20:37:34 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * only numeric arg, but the input is a string,
	so i have to create a func that check if is a string num:
 *  - numeric argument required
 * Exit with a true value: exit 0
 * Exit with a false value: exit 1
 * 126: A file to be executed was found, but it was not  an  executable utility.
 * 127: A utility to be executed was not found.
 * >128: A command was interrupted by a signal.
 * in case of: exit ARG_NUM ARG_NUM:
 *  bash: exit: too many arguments
 *

*/

int	is_valid_number(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (1);
	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
			return (1);
		str++;
	}
	return (0);
}

void	ft_exit(t_data *data)
{
	char	**args;
	int		exit_status;

	exit_status = data->exit_code;
	args = data->tokens->args;
	if (args[0][0] != '\0')
	{
		if (is_valid_number(args[0]) == 0)
		{
			exit_status = ft_atoi(args[0]);
			if (args[1])
			{
				exit_status = exit_many_args(data, exit_status);
				return ;
			}
			if (exit_status >= -2147483648 && exit_status <= 2147483647)
				exit_status = exit_status % 256;
			else
				exit_status = 1;
		}
		else
			ft_exit_255(data, args[0]);
	}
	free_exit(data, exit_status);
}

int	exit_many_args(t_data *data, int exit_status)
{
	write(2, "exit\n", 5);
	write(2, "minishell: exit: too many arguments\n", 36);
	exit_status = 1;
	if (data->childn->pids)
	{
		end_child(data);
		exit(exit_status % 256);
	}
	return (exit_status);
}

void	free_exit(t_data *data, int exit_status)
{
	data->free_code = F_ENV;
	if (data->childn->pids)
		end_child(data);
	else
	{
		free_all(data);
		write(1, "exit\n", 5);
	}
	exit(exit_status % 256);
}
