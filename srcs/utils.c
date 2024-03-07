/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:57:56 by kmoraga           #+#    #+#             */
/*   Updated: 2024/03/07 11:45:47 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

int is_delimiter(char c)
{
    return (c == '|' || c == '>' || c == '<');
}

void parse_command(char *input, int *index, t_token *tokens) {
    
        int i = *index;
        int start;
        // Saltar los espacios en blanco
        while (input[i] != '\0' && is_whitespace(input[i]))
            i++;
        start = i; // Guardar el inicio del token
        // Copiar el token hasta encontrar un delimitador o el final de la cadena
        while (input[i] != '\0' && !is_delimiter(input[i]) && !is_whitespace(input[i]))
            i++;

        // Asignar memoria para el token y copiarlo
        tokens->cmd = malloc(i - start + 1); // +1 para el carácter nulo
        if (tokens->cmd == NULL) {
            // Manejar el error de memoria
            return;
        }

        strncpy(tokens->cmd, &input[start], i - start);
        tokens->cmd[i - start] = '\0'; // Agregar el carácter nulo al final del token

        *index = i; // Actualizar el índice para apuntar al próximo token
}

void parse_args(char *input, int *index, t_token *tokens)
{
    int i = *index;
    int start = i;

    // Saltar los espacios en blanco
    while (input[i] != '\0' && is_whitespace(input[i]))
        i++;

    start = i; // Guardar el inicio del token

    // Copiar el token hasta encontrar un delimitador o el final de la cadena
    while (input[i] != '\0' && !is_delimiter(input[i]))
        i++;

    // Si no se encontró ningún argumento, asignar NULL a tokens->args
    if (start == i) {
        tokens->args = NULL;
    } else {
        // Asignar memoria para el token y copiarlo
        tokens->args = malloc(i - start + 1); // +1 para el carácter nulo
        if (tokens->args == NULL) {
            // Manejar el error de memoria
            return;
        }

        strncpy(tokens->args, &input[start], i - start);
        tokens->args[i - start] = '\0'; // Agregar el carácter nulo al final del token
    }

    *index = i; // Actualizar el índice para apuntar al próximo token
}

void detect_delimiter(char* input, int* index, t_token* new_token) 
{
    if (input[*index] == '|') {
        new_token->delim = PIPE;
        (*index)++; // Skip the delimiter
    } else if (input[*index] == '>') {
        new_token->delim = REDIR_O;
        (*index)++; // Skip the delimiter
    } else if (input[*index] == '<') {
        new_token->delim = REDIR_I;
        (*index)++; // Skip the delimiter
    } else {
        new_token->delim = CMD;
    }
}

int check_builtins(t_token *token)
{
    if(strcmp(token->cmd, "echo") == 0)
        return 1;
    else if(strcmp(token->cmd, "cd") == 0)
        return 1;
    else if(strcmp(token->cmd, "pwd") == 0)
        return 1;
    else if(strcmp(token->cmd, "export") == 0)
        return 1;
    else if(strcmp(token->cmd, "unset") == 0)
        return 1;
    else if(strcmp(token->cmd, "env") == 0)
        return 1;
    else if(strcmp(token->cmd, "exit") == 0)
        return 1;
    else
        return 0;
}