/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creuther <creuther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/14 21:33:30 by creuther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*piping(t_data *data)
{
	data->childn->cnt_childn = count_pipes(data);
	if (malloc_fds(data) != 0)
		return (data);
	data->tokens = move_to_first_token(data->tokens);
	return (data);
}

int	count_pipes(t_data *data)
{
	int	cnt;
	int	pipe_num;

	cnt = 1;
	pipe_num = 1;
	if (data->tokens->next)
		data->tokens = data->tokens->next;
	while (cnt < data->token_num && data->tokens)
	{
		if (data->tokens->delim == PIPE)
			pipe_num++;
		cnt++;
		if (data->tokens->next)
			data->tokens = data->tokens->next;
	}
	data->tokens = move_to_first_token(data->tokens);
	return (pipe_num);
}

int	malloc_fds(t_data *data)
{
	int	i;

	i = 0;
	if (data->childn->cnt_childn == 1)
		return (0);
	if (ft_calloc(data, F_INPUT, (void *)&data->childn->pipes, sizeof(int *)
			* (data->childn->cnt_childn)) == 1)
		return (1);
	while (i < (data->childn->cnt_childn - 1))
	{
		if (ft_calloc(data, F_PIPES, (void *)&data->childn->pipes[i],
				sizeof(int) * 2) == 1)
			return (1);
		i++;
	}
	if (fill_fds(data) == 1)
		return (1);
	return (0);
}

int	fill_fds(t_data *data)
{
	int	i;

	i = 0;
	while (i < (data->childn->cnt_childn - 1))
	{
		if (pipe(data->childn->pipes[i]) == -1)
		{
			input_error(data, F_PIPES, 32, "Error: pipe creation failed");
			free_pipes(data->childn->pipes, data);
			return (1);
		}
		i++;
	}
	return (0);
}

// input = read from lower num = 0
// output = write in own num = 1
