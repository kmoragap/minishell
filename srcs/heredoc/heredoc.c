/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:41:39 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/29 15:52:45 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*heredoc(t_data *data)
{
	int	i;

	i = 1;
	while (i < data->token_num && data->tokens && data->tokens->next)
	{
		if (data->tokens->next && data->tokens->next->delim == REDIR_H)
		{
			init_signals(HEREDOC);
			handle_heredoc(data->tokens, data->env, data->exit_code);
		}
		if (!data->tokens->next)
			break ;
		data->tokens = data->tokens->next;
	}
	data->tokens = move_to_first_token(data->tokens);
	return (data);
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_sigint = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	handle_heredoc(t_token *token, char **env, int status)
{
	int	fd;

	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	read_in_here(token, env, fd, status);
	init_signals(IGNORE);
	if (g_sigint)
	{
		unlink(".heredoc_tmp");
		return ;
	}
}

void	read_in_here(t_token *token, char **env, int fd, int status)
{
	char	*line;

	g_sigint = 0;
	while (!g_sigint)
	{
		line = readline("> ");
		if (!line || g_sigint || ft_strcmp(line, token->next->cmd) == 0)
			break ;
		if (token->next->quotes == 0)
			line = expander_fun(line, env, status);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	close(fd);
}

int	has_quotes(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == 34 || cmd[i] == 39)
			return (1);
		i++;
	}
	return (0);
}
