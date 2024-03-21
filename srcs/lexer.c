/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:46:13 by kmoraga           #+#    #+#             */
/*   Updated: 2024/03/14 14:37:49 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int check_type_tk(char *token)
{
    //check the type of the token
    int i;

    i = 0;
    while(token[i] != '\0')
    {
        if(token[i] == '|')
            return (PIPE);
        if(token[i] == '>')
            return (REDIR_O);
        if(token[i] == '<')
            return (REDIR_I);
        if(token[i] == '$')
            return (EXPAND);
        i++;
    }
    return (CMD);
}

t_token *tokenizer(char *input) {
    t_token *tokens = NULL;
    t_token *start = NULL;
    t_token *prev = NULL;
    
    int id = 0;
    int index = 0;
    while(input[index] != '\0') 
    {
        t_token *new_token = malloc(sizeof(t_token));
        if(new_token == NULL)
            return NULL;
        new_token->id = id++;
        parse_command(input, &index, new_token);
        parse_args(input, &index, new_token);
        new_token->type = check_type_tk(new_token->cmd);
        new_token->next = NULL;
        new_token->prev = prev;
        if(tokens == NULL) {
            tokens = new_token;
            start = tokens;
        } else {
            prev->next = new_token;
        }
        detect_delimiter(input, &index, new_token);
        prev = new_token;
    }
    return start;
}

void lexer(t_data **data)
{
    (*data)->tokens = tokenizer((*data)->input);
    //check_tokens_lst((*data)->tokens);
    // Additional processing if needed
    // Free tokens when done
    // free_tokens((*data)->tokens);
}







/**
 * IDEA:
 * verificar/eliminar los espacios
 * tomar el input y esperar hasta que haya un operador para dividirlo o también hasta que haya un NULL terminator
 * Una vez se sabe el divisor, lo toma y crea el token con el ID correspondiente
 * A su vez le asigna el divisor al primer token, solamente si hay divisor
 * Esto con el fin de que en el momento de preparar los comandos para su ejecucion se se sepa si hay o no un divisor
*/

