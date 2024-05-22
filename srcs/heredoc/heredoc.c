/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:41:39 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/22 14:45:21 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * g_heredoc_interrupted
 * →signals
 * →hidden file
 * → “>”
 * get_next_line ??
 * Abrir un archivo temporal (.heredoc) para escribir las entradas del usuario.
 * Capturar señales para manejar interrupciones (como Ctrl+C).
 * Leer líneas de entrada del usuario hasta que la línea coincida exactamente con el delimitador.
 * Expandir variables y manejar comillas si necesario antes de escribir en el archivo.
 * Cerrar y reabrir el archivo en modo de lectura.
 * 0644 permisos individuales de lectura y escritura para el propietario y solo lectura para los demás.
 * Remove the temporary file if interrupted
 * esto se utiliza para almacenar el manejador de 
 * señales previamente configurado para que pueda ser restaurado después de modificar el manejador para el heredoc.
 * la función devuelve el manejador de señales anterior
 * Esto nos permite guardar el manejador previo y restaurarlo más tarde,
 * asegurando que nuestro cambio temporal no tenga efectos a largo plazo en el programa
 * 
 * guardar la linea en un char *line
 * close(STDIN_FILENO) interrumpe la lectura, causando que readline falle y el bucle termine.
 * */

t_data *heredoc(t_data *data)
{
    int i;

    i = 1;
    while (i < data->token_num && data->tokens && data->tokens->next)
    {
        if (data->tokens->next && data->tokens->next->delim == REDIR_H)
            handle_heredoc(data->tokens, data->env, data->exit_code);
        if (!data->tokens->next)
            break;
        data->tokens = data->tokens->next;
    }
    data->tokens = move_to_first_token(data->tokens);
    return (data);
}

static int g_heredoc_interrupted = 0;

void handle_sigint_heredoc(int sig)
{
    (void)sig;
    g_heredoc_interrupted = 1;
    write(STDOUT_FILENO, "\n", 1);
    close(STDIN_FILENO);
}

void handle_heredoc(t_token *token, char **env, int status)
{
    char *line;
    int fd;
    void (*prev_handler)(int);

    prev_handler = signal(SIGINT, handle_sigint_heredoc);
    //printf("hola\n");
    fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return ;
    g_heredoc_interrupted = 0;
    while (!g_heredoc_interrupted)
    {
        line = readline("> ");
        if (!line || g_heredoc_interrupted || ft_strcmp(line, token->next->cmd) == 0)
            break;
        if(token->next->quotes == 0)
            line = check_expand_quotes(line, env, status);
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
        line = NULL;
    }
    if (line)
        free(line);
    close(fd);

    signal(SIGINT, prev_handler); // restaur el signal previo

    if (g_heredoc_interrupted)
    {
        unlink(".heredoc_tmp"); //remover el archivo temporal
        return ;
    }
}

int     has_quotes(char *cmd)
{
   int  i;

   i = 0;
   while (cmd[i])
   {
       if (cmd[i] == 34 || cmd[i] == 39)
           return (1);
       i++;
   }
   return (0);
}

