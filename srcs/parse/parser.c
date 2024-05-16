/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creuther <creuther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/14 21:02:45 by creuther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_data  *parser(t_data *data)
{
    if (!data->input[0])
        return (data);
    while ((data)->tokens->id < (data)->token_num)
    {
        if (check_empty_cmd(data->tokens, data) == 1)
            return (data);         
        else if (check_expand(data->tokens, data->env) == 1)
            (data->tokens)->type = EXPAND;
        else if (check_fd(data->tokens) == 1)
            (data->tokens)->type = FD;
        else if (check_file(data->tokens) == 1)
            (data->tokens)->type = FLE;
        else
            (data->tokens)->type = CMD;
        if ((data->tokens)->id == ((data)->token_num - 1))
            break;
        data->tokens = (data->tokens)->next;
    }
    data->tokens = move_to_first_token(data->tokens);
    return (data);
}

int     check_empty_cmd(t_token *move, t_data *data)
{
    if ((move)->cmd && (move)->cmd[0])
        return (0);
    input_error(data, F_TOKS, "\n");
    return (1);
}

int check_expand(t_token *move, char **env)
{
    if (check_expand_var(move->cmd))
    {
        expand_cmd(move, env);
        return (1);
    }

    if(move->args_num != 0)
    {
       expand_args(move, env);
       return (1);   
    }
    return (0);
}

int     check_fd(t_token *move)
{
    if ((move)->delim == 6 || (move)->delim == 7 || (move)->delim == 8 || (move)->delim == 9)
    {
        if ((move)->cmd[0] == '&' && (move)->cmd[1] >= '0' && (move)->cmd[1] <= '9')
            return (1);
    }
    return (0);
}

int     check_file(t_token *move)
{
    if ((move)->delim == 6 || (move)->delim == 7 || (move)->delim == 8 || (move)->delim == 9)
        return (1);
    return (0);
}
