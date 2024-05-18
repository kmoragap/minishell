/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:41:39 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/18 19:33:00 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
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
*/


/*
void execute_command_with_heredoc(t_data *data)
{
    int fd = open(".heredoc_tmp", O_RDONLY);
    if (fd < 0) return;

    dup2(fd, STDIN_FILENO);
    close(fd);
    execve(data->tokens->cmd, data->tokens->args, data->env);
}
*/

void handle_heredoc(t_token *token) 
{
    char *line;
    int fd;
    
    fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) 
        return ;
    
    while (1) 
    {
        line = readline("> ");
        if (ft_strcmp(line, token->cmd) == 0) 
            break;
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    close(fd);
}