/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/26 19:34:51 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_error(t_data *data, t_free code, int exit_code, char *txt)
{
	data->err_code = ER_INPUT;
	data->free_code = code;
	data->exit_code = exit_code;
	write(2, txt, ft_strlen(txt));
}

void	malloc_error(t_data *data, t_free code)
{
	if (data)
	{
		data->free_code = code;
		data->err_code = ER_MALLOC;
		data->exit_code = 12;
	}
	write(2, "Error: malloc failure\n", 22);
}
