/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:20:49 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/26 22:59:48 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		g_sigint = 130;
	}
}

static void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
	}
}

void	init_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}

void	handle_eof(t_data *data)
{
	// write(1, "exit\n", 5);
	data->free_code = 100;
	free_all(data);
	exit(0);
}
