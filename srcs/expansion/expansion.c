/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:26:56 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/11 20:55:06 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char *preprocess_token(char *token, int exit_status, int pa) 
{
    char *processed_tok;
    char *value;

    processed_tok = remove_outer_quotes(token);

    if (processed_tok == NULL) 
        return NULL;

    processed_tok = remove_outer_parentheses(processed_tok);
    if (processed_tok == NULL)
       return NULL;
    else
        pa = 1;

    value = check_special_expand(token, exit_status);
    if (value != NULL)
        return value;

    return processed_tok;
}



static char *resolve_token_value(char *token, char **env, int exit_status, int pa)
{
    int i;
    char *var;
    char *value;

    i = 0;
    var = NULL;
    value = NULL;

    while (env[i] != NULL) 
    {
        var = ft_strchr_before_c(env[i], '=');
        value = ft_strchr(env[i], '=');
        if (ft_strcmp(var, token) == 0) 
        {
            if(value[0] == '$')
            {
                value = expand_token(value, env, exit_status);
                if (value != NULL)
                    return ft_strdup(value);
            }
            if(pa == 1)
                // poner parentesis ?????????????????????????????????????????????????????????????????????????ß
            return ft_strdup(value);
        }
        i++;
    }
    return NULL;
}


char *expand_token(char *token, char **env, int exit_status) 
{
    char *processed_tok;
    int pa;

    pa = 0;

    processed_tok = preprocess_token(token, exit_status, pa);
    if (processed_tok == NULL)
        return NULL;

    processed_tok++;
    return resolve_token_value(processed_tok, env, exit_status, pa);
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
        else
            printf("Error\n");
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
            else
                printf("Error acá\n"); 
        }
        else
            printf("Error aca\n");        
        i++;
    }    
}
