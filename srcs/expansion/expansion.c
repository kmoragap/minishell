/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:26:56 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/20 01:08:40 by kmoraga          ###   ########.fr       */
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

static char *preprocess_token(char *token, int exit_status) 
{
    char *processed_tok;
    char *value;


    processed_tok = remove_outer_quotes(token);

    if (processed_tok == NULL) 
        return NULL;


    /*processed_tok = remove_outer_parenthesis(processed_tok);
    if (processed_tok == NULL)
       return NULL;
*/
    value = check_special_expand(token, exit_status);
    if (value != NULL)
        return value;

    return processed_tok;
}




static char *resolve_token_value(char *token, char **env, int exit_status)
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
        value = ft_strchr_after_c(env[i], '=');
        if (ft_strcmp(var, token) == 0) 
        {
            if(value && value[0] == '$')
            {
                value = expand_token(value, env, exit_status);
                if (value != NULL)
                    return ft_strdup(value);
            }
            return ft_strdup(value);
        }
        i++;
    }
    return ft_strdup(" ");
}


char *expand_token(char *token, char **env, int status) 
{
    char *processed_tok;

    processed_tok = preprocess_token(token, status);
    if (processed_tok == NULL)
        return NULL;
    else if(ft_strnum(processed_tok))
        return processed_tok;
    
    if(ft_strchr(processed_tok, '$') == 1)
        return ft_strdup(processed_tok);
    else
        processed_tok++;
    return resolve_token_value(processed_tok, env, status);
}

void expand_cmd(t_token *token, char **env, int status) 
{
    char *expanded_cmd;
    expanded_cmd = NULL;

    if (check_expand_var(token->cmd)) 
    {
        expanded_cmd = expand_token(token->cmd, env, status);
        if (expanded_cmd != NULL) 
        {
            free(token->cmd); 
            token->cmd = expanded_cmd; 
        }
    }
}

/**
 * 
 * acá deberia ir a través de los args y revisar cada uno si es que hay 
 * entre "" y devolver cada uno de los valores expandidos (si es que los hay)
 * para luego reemplazarlos con su valor expandido
 * dentro de " los separadores pueden ser en ASCII:
 * 32 a 35
 * 37 a 47
 * NUMEROS NO INTERPRETAR
 * 58 a 64
 * 91 a 96
 * 123 a 126"
 * 
*/
 static char valid_delim_expand(char c) {
    if ((c >= 32 && c <= 33) || c == 35 || (c >= 36 && c <= 47) || (c >= 58 && c <= 64) ||
        (c >= 91 && c <= 96) || (c >= 123 && c <= 126)) 
        return c;
    return 0;
}

static char *expand_variable(char *var, char **env, int status) 
{
    char *expanded; 
    
    expanded = expand_token(var, env, status);
    if (expanded)
        return expanded;
    else
        return ft_strdup(var);
}

static char *check_expand_quotes(char *arg, char **env, int status) 
{
    char *result;
    char *temp;
    char *var_name;
    char *new_result;
    char delim[2];
    int start;
    int end;
    int len;

    result = ft_strdup("");
    temp = NULL;
    var_name = NULL;
    new_result = NULL;
    start = 0;
    end = 0;
    len = ft_strlen(arg);

    while (end <= len) 
    {
        if (arg[end] == '\0' || valid_delim_expand(arg[end]) || (arg[end] == '$' && end > start))
        {
            if (end > start)
            {
                var_name = ft_strndup(&arg[start], end - start);
                temp = expand_variable(var_name, env, status);
                new_result = ft_strjoin(result, temp);
                free(result);
                free(temp);
                result = new_result;
                free(var_name);
            }
            if (arg[end] != '\0') 
            {
                delim[0] = arg[end];
                delim[1] = '\0';// No avanzar el start aún
                if (delim[0] == '$') 
                    start = end;
                else 
                {
                    new_result = ft_strjoin(result, delim);
                    free(result);
                    result = new_result;
                    start = end + 1;
                }
            }
            else
                start = end + 1;
        }
        end++;
    }
    return result;
}


void expand_args(t_token *token, char **env, int status) 
{
    char *expanded_arg;
    int i;

    expanded_arg = NULL;
    i = 0;
    printf("before parser arg: %s\n", token->args[i]);
    while (token->args[i] != NULL)
    {
        if (token->args_num == 1)
        {
            expanded_arg = check_expand_quotes(token->args[i], env, status);
            if (expanded_arg != NULL)
            {
                free(token->args[i]);
                token->args[i] = expanded_arg;
            }
        }
        else if (token->args_num > 1 )
        {
            if (check_expand_args(&token->args[i]) == 1)
            {
                expanded_arg = expand_token(token->args[i], env, status);
                if (expanded_arg != NULL)
                {
                    free(token->args[i]);
                    token->args[i] = expanded_arg;
                }
            }
        }
        i++;
    }    
}
