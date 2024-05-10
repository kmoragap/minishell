/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_special_cases.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:28:19 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/10 18:38:02 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *concatenate_exit_string(const char *exit_status_str, const char *rest_of_special)
{
    size_t total_size;
    char *result;

    total_size = ft_strlen(exit_status_str) + ft_strlen(rest_of_special) + 1;
    result = ft_calloc_norm(total_size, sizeof(char));
    if (result == NULL) 
    {
        free((void *)exit_status_str);
        return NULL;
    }

    ft_strcat(result, exit_status_str);
    ft_strcat(result, rest_of_special);
    free((void *)exit_status_str);
    return result;
}

char *check_special_expand(char *special, int exit_status) 
{
    char *exit_status_str;


    exit_status_str = NULL;
    
    if (special[0] == '$' && special[1] == '?') 
    {
        exit_status_str = ft_itoa(exit_status);
        if (special[2] != '\0' && ft_isalnum(special[2])) 
            return concatenate_exit_string(exit_status_str, special + 2);
        else 
            return exit_status_str;
    }
    return NULL;
}


static int has_outer_quotes(char *arg) 
{
    size_t len;
    
    len = ft_strlen(arg);
    if (len < 2)
        return 0; 

    return ((arg[0] == '"' && arg[len - 1] == '"') || (arg[0] == '\'' && arg[len - 1] == '\''));
}

char *remove_outer_quotes(char *arg) 
{
    char *new_arg;
    size_t len;

    len = 0;
    new_arg = NULL;
    if(has_outer_quotes(arg))
    {
        len = ft_strlen(arg);
        new_arg = ft_calloc_norm(len - 1, sizeof(char));
        if (new_arg == NULL)
            return NULL;
        ft_strncpy(new_arg, arg + 1, len - 2);
        new_arg[len - 2] = '\0';
        return new_arg;
    }
    
    return ft_strdup(arg);
}