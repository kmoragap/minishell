/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:46:13 by kmoraga           #+#    #+#             */
/*   Updated: 2024/03/01 16:34:49 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int check_type_tk(char *token)
{
    if (strcmp(token, "|") == 0)
        return (PIPE);
    if (strcmp(token, ">") == 0)
        return (REDIR_O);
    if (strcmp(token, "<") == 0)
        return (REDIR_I);
    return (WORD);
}

/*
    *is not complete yet :(
    *is a very simple version, has to be improved bc it does not handle errors
    *it does not free the memory...
    *have to be more efficient tokenizing the input, bc is not working on somes cases, like "ls|wc"
*/
int is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

char *get_token(char *input)
{

    int i;

    if(is_whitespace(*input))
        input++;
    if(*input == '\0')
        return NULL;
    i = 0;
    while(input[i] != '\0' && !is_whitespace(input[i]))
    {
        //split the input by operators | < > 
        if(input[i] == '|' || input[i] == '<' || input[i] == '>')
        {
            if(i == 0)
            {
                i++;
                break;
            }
            break;
        }
        i++;
    }
    return strndup(input, i);
}

t_token *split_input(char *input)
{
    t_token *tokens;
    t_token *prev;
    t_token *start;
    char *token;
    int i;

    tokens = malloc(sizeof(t_token)); // maybe use own ft_calloc
    // implement a error function
    start = tokens;
    prev = NULL;
    i = 0;
    
    //delimit the input by spaces operators
    token = get_token(input); 
    while (token != NULL)
    {
        tokens->content = token;
        tokens->type = check_type_tk(token);
        tokens->id = i;
        tokens->prev = prev;       
        if(input[i] != '\0') {
            tokens->next = malloc(sizeof(t_token));
            // implement a error function
            prev = tokens;
            tokens = tokens->next;
        } else {
            tokens->next = NULL;
        }
        
        // Update input to point to the start of the next token
        input += strlen(token) + 1; // +1 to skip the space or operator
        token = get_token(input);
        i++;
    }
    if(prev)
        prev->next = NULL;
    return start;
}
/**
 * create simples command with the tokens
*/


/**
 * IDEA:
 * verificar los espacios
 * tomar el input y esperar hasta que haya un operador para dividirlo o también hasta que haya un NULL terminator
 * Una vez se sabe el divisor, lo toma y crea el token con el ID correspondiente
 * A su vez le asigna el divisor al primer token, solamente si hay divisor
 * Esto con el fin de que en el momento de preparar los comandos para su ejecucion se se sepa si hay o no un divisor
*/



void lexer(t_data **data)
{
    (*data)->tokens = split_input((*data)->input);
    check_tokens_lst((*data)->tokens);
}