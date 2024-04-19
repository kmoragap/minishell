/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:34:33 by kmoraga           #+#    #+#             */
/*   Updated: 2024/04/19 17:49:27 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_expand_var(char *var)
{
    if (var[0] == '$' && (is_valid_variable_char(var[1])))
        return (1);
    else if (var[0] == 34 && var[1] == '$' && is_valid_variable_char(var[2]))
        return (1);
    return (0);
}

int is_valid_variable_char(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9') || c == '_' || c == '?' || c == '(';
}

int check_expand_args(char **args)
{
    int i; 
    int j;
    int k;
    
    i = 0;
    while (args[i] != NULL) {
        j = 0;
        while (args[i][j] != '\0') {
            if (args[i][j] == '$' && args[i][j + 1] != '\0' && args[i][j + 1] != ' ') {
                k = j + 1;
                while (is_valid_variable_char(args[i][k])) {
                    k++;
                }
                if (k > j + 1) {
                    return 1;
                }
            }
            j++;
        }
        i++;
    }
    return 0;
}

char *check_special_expand(char *special, int exit_status)
{
    char *exit_status_str;
    char *rest_of_special;
    char *result;

    exit_status_str = NULL;
    rest_of_special = NULL;
    result = NULL;

    if(special[0] == '$' && special[1] == '?')
    {
        if(special[2] != '\0' && ft_isascii(special[2]))
        {
            exit_status_str = ft_itoa(exit_status);
            rest_of_special = special + 2;
            result = malloc(strlen(exit_status_str) + strlen(rest_of_special) + 1);
            strcpy(result, exit_status_str);
            strcat(result, rest_of_special);
            free(exit_status_str);
            return result;
        }
        else
            return ft_itoa(exit_status);
    }
    else if(special[0] == '$' && ft_isascii(special[1]))
        return strdup("");
    else
        return NULL;
}


int check_expand_quotes(const char *str) 
{
    int len;
    int i;
    
    len = strlen(str);
    i = 1;
    
    if (len < 4) // Minimum length to contain "$()"
        return 0;
    if (str[0] != '\"' || str[len-1] != '\"') 
        return 0;
    while (i < len - 2) 
    {
        if (str[i] == '$' && ((ft_isalnum(str[i+1]) && str[i+2] == '(') || str[i+1] == '(')) 
            return 1;
        i++;
    }
    return 0;
}