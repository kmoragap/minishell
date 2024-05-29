/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:20:49 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/29 15:52:55 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(STDIN_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_sigint = 130;
	}
}

void	set_signal_handler(int signal_type, int sig, void (*handler)(int))
{
	if (signal_type == ACTIVE || signal_type == HEREDOC)
		signal(sig, handler);
	else if (signal_type == DEFAULT)
		signal(sig, SIG_DFL);
	else if (signal_type == IGNORE)
		signal(sig, SIG_IGN);
}

void	init_signals(int sig)
{
	if (sig == ACTIVE)
	{
		set_signal_handler(ACTIVE, SIGINT, handle_sigint);
		set_signal_handler(ACTIVE, SIGQUIT, SIG_IGN);
	}
	else if (sig == DEFAULT)
	{
		set_signal_handler(DEFAULT, SIGINT, SIG_DFL);
		set_signal_handler(DEFAULT, SIGQUIT, SIG_DFL);
	}
	else if (sig == IGNORE)
	{
		set_signal_handler(IGNORE, SIGINT, SIG_IGN);
		set_signal_handler(IGNORE, SIGQUIT, SIG_IGN);
	}
	else if (sig == HEREDOC)
	{
		set_signal_handler(HEREDOC, SIGINT, handle_sigint_heredoc);
		set_signal_handler(HEREDOC, SIGQUIT, SIG_IGN);
	}
}

void	handle_eof(t_data *data)
{
	// write(1, "exit\n", 5);
	data->free_code = 100;
	free_all(data);
	exit(0);
}