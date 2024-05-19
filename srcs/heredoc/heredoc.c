/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:41:39 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/19 16:35:34 by kmoraga          ###   ########.fr       */
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


static int g_heredoc_interrupted = 0;

void handle_sigint_heredoc(int sig)
{
    (void)sig;
    g_heredoc_interrupted = 1;
    write(1, "\n", 1);
    close(STDIN_FILENO);
}

void handle_heredoc(t_token *token)
{
    char *line;
    char *temp;
    int fd;
    void (*prev_handler)(int);

    token->heredoc = ft_strdup("");
    prev_handler = signal(SIGINT, handle_sigint_heredoc);
    printf("hola\n");
    fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return ;
    g_heredoc_interrupted = 0;
    while (!g_heredoc_interrupted)
    {
        line = readline("> ");
        if (!line || g_heredoc_interrupted || ft_strcmp(line, token->next->cmd) == 0)
            break;
        temp = token->heredoc;
        token->heredoc = ft_strjoin(token->heredoc, line);
        free(temp);
        token->heredoc = ft_strjoin(token->heredoc, "\n");
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    if (line)
        free(line);
    close(fd);

    signal(SIGINT, prev_handler); // restaur el signal previo

    if (g_heredoc_interrupted)
    {
        unlink(".heredoc_tmp"); //remover el archivo temporal
        token->heredoc = NULL;
        free(temp);
        return ;
    }

    //printf("content:\n");
    //printf("%s\n", token->heredoc);
    unlink(".heredoc_tmp");
}
