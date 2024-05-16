/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:20:49 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/16 20:52:31 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * ctrl+c SIGINT:  Genera una nueva línea de comandos sin terminar el shell
 * ctrl+d EOF: Si el usuario presiona ctrl-D (que se interpreta como un EOF en la entrada estándar), puedes terminar el bucle y cerrar el shell
 * ctrl+\ SIGQUIT:  No hace nada
 * 
**/

static void handle_sigint(int sig)
{
    if (sig == SIGINT)
    {
        write(1, "\n", 1);
        rl_on_new_line();
		rl_replace_line("", 0);
        rl_redisplay();
    }
}

static void handle_sigquit(int sig)
{
    (void)sig;
    printf("estoy haciendo esta wea\n");
    rl_on_new_line();
	rl_replace_line("", 0);
    rl_redisplay();
}

void init_signals(void)
{
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, handle_sigquit);
}
/**
 * esto hay que verlo de más cerca, ya que debería eliminar lo que se ha
 * asignado hasta el momento, entonces hay que manipular eso cuidadosamente
 * para evitar un seg fault;
*/
void handle_eof(t_data *data)
{
    printf("exit\n");
    free(data->input);
    data->input = NULL;
    free_all(data);
    exit(0);
}