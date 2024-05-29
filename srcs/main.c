/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:38:23 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/29 19:02:30 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_sigint;

t_data	*in_data(t_data *re, int num, char **envp)
{
	int	j;

	j = 0;
	while (j < num)
	{
		re->env[j] = ft_strdup(envp[j]);
		j++;
	}
	re->env_len = num;
	re->err_code = ER_NO;
	re->free_code = 100;
	re->childn = ft_calloc_norm(1, sizeof(t_child));
	if (!re->childn)
	{
		free(re);
		return (NULL);
	}
	return (re);
}

t_data	*init_data(char **envp)
{
	t_data	*re;
	int		i;

	re = NULL;
	if (ft_calloc(NULL, F_INPUT, (void *)&re, sizeof(t_data)) == 1)
		return (NULL);
	re->env_len = 0;
	re->input = NULL;
	i = 0;
	while (envp[i])
		i++;
	if (ft_calloc(re, F_INPUT, (void *)&re->env, (sizeof(char *) * (i + 2))))
	{
		free(re);
		return (NULL);
	}
	re = in_data(re, i, envp);
	if (!re)
		return (NULL);
	return (re);
}

void	read_input(t_data **data)
{
	char	*line;
	char	*tmp;

	if (isatty(fileno(stdin)))
		line = readline(PROMPT);
	else
	{
		tmp = get_next_line(fileno(stdin));
		line = ft_strtrim(tmp, "\n");
		free(tmp);
	}
	// line = readline(PROMPT);
	if (!line)
		handle_eof((*data));
	if (*line)
		add_history(line);
	(*data)->input = line;
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = init_data(env);
	if (!data)
		return (1);
	shlvl(data);
	while (1)
	{
		init_signals(ACTIVE);
		read_input(&data);
		init_signals(IGNORE);
		data->free_code = NO_FREE;
		if (data->err_code == ER_NO)
			data->tokens = tokenizer(data);
		if (data->err_code == ER_NO)
			data = parser(data);
		if (data->err_code == ER_NO)
			data = execute_token(data);
		free_all(data);
	}
}
