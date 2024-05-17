/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:26:56 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/17 18:01:13 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * probablemente tenga que realizar un cambio acá
 * la idea es que deconstruya el string y luego lo vuelva a construir
 * en caso de -> echo "($PWD)"
 * debería, primero, sacar las comillas.
 * -> ($PWD)
 * luego debería sacar los parentesis -> ($PWD)
 * -> $PWD
 * para luego expandir la variable
 * Y SI esto está entre parentesis, activar una varáible que reconstruya el string en este caso con la variable expandida
 * -> (/home/kris/)
*/

static char *preprocess_token(char *token, int exit_status, int *parenthesis) 
{
    char *processed_tok;
    char *value;

    processed_tok = remove_outer_quotes(token);

    if (processed_tok == NULL) 
        return NULL;

    processed_tok = remove_outer_parenthesis(processed_tok);
    if (processed_tok == NULL)
       return NULL;
    else
        *parenthesis = 1;

    value = check_special_expand(token, exit_status);
    if (value != NULL)
        return value;

    return processed_tok;
}


/*
static char *add_parenthesis(char *value)
{
    char *new_value;
    int value_length;

    new_value = NULL;

    value_length = ft_strlen(value);
    new_value = ft_calloc_norm((value_length + 3), sizeof(char));
    if (new_value == NULL)
        return NULL;

    new_value[0] = '(';
    ft_strcat(new_value + 1, value);
    new_value[value_length + 1] = ')';
    new_value[value_length + 2] = '\0';
    return new_value;

}*/


static char *resolve_token_value(char *token, char **env, int exit_status, int parenthesis)
{
    int i;
    int value_length;
    char *var;
    char *value;
    char *new_value;

    i = 0;
    var = NULL;
    value = NULL;
    new_value = NULL;

    while (env[i] != NULL) 
    {
        var = ft_strchr_before_c(env[i], '=');
        value = ft_strchr_after_c(env[i], '=');
        if (ft_strcmp(var, token) == 0) 
        {
            if(value && value[0] == '$')
            {
                value = expand_token(value, env, exit_status);
                if (value != NULL)
                    return ft_strdup(value);
            }
            else if(parenthesis)
            {
                value_length = ft_strlen(value);
                new_value = ft_calloc_norm((value_length + 3), sizeof(char));
                if (new_value == NULL) return NULL;
                new_value[0] = '(';
                ft_strcat(new_value + 1, value);
                new_value[value_length + 1] = ')';
                new_value[value_length + 2] = '\0';
                return new_value;

            }
            return ft_strdup(value);
        }
        i++;
    }
    return NULL;
}


char *expand_token(char *token, char **env, int exit_status) 
{
    char *processed_tok;
    int parenthesis;

    parenthesis = 0;

    processed_tok = preprocess_token(token, exit_status, &parenthesis);
    if (processed_tok == NULL)
        return NULL;

    processed_tok++;
    return resolve_token_value(processed_tok, env, exit_status, parenthesis);
}

void expand_cmd(t_token *token, char **env) 
{
    char *expanded_cmd;
    expanded_cmd = NULL;

    if (check_expand_var(token->cmd)) 
    {
        expanded_cmd = expand_token(token->cmd, env, token->exit_status);
        if (expanded_cmd != NULL) 
        {
            free(token->cmd); 
            token->cmd = expanded_cmd; 
        }
    }
}

void expand_args(t_token *token, char **env) 
{
    char *expanded_arg;
    int i;
    
    expanded_arg = NULL;
    i = 0;

    while(token->args[i] != NULL)
    {
        if(check_expand_args(&token->args[i]) == 1)
        {
            expanded_arg = expand_token(token->args[i], env, token->exit_status);
            if (expanded_arg != NULL) 
            {
                free(token->args[i]); 
                token->args[i] = expanded_arg;
            }
        }
        i++;
    }    
}
