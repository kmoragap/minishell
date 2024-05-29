/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 12:15:14 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/28 20:37:34 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_child(t_data *data)
{
	data->free_code = F_ENV;
	free(data->childn->pids);
	close_pipes(data, -1);
	free_pipes(data->childn->pipes, data);
	free_all_child(data);
}

void	ft_exit_255(t_data *data, char *args)
{
	write(2, "minishell: exit: ", 17);
	write(2, args, ft_strlen(args));
	write(2, ": numeric argument required\n", 28);
	data->free_code = F_ENV;
	if (data->childn->pids)
		end_child(data);
	else
		free_all(data);
	exit(2);
}
