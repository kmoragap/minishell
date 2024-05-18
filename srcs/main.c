/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:38:23 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/18 15:44:39 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data *init_data(char **envp)
{
    t_data *re;
    int i;
    int j;

    re = NULL;
    if(ft_calloc(re, F_INPUT, (void *)&re, sizeof(t_data)) == 1)
        return NULL;
    re->env_len = 0;
    re->input = NULL;
    i = 0;
    while(envp[i])
        i++;
    if(ft_calloc(re, F_INPUT, (void *)&re->env, (sizeof(char *) * (i + 2))) == 1)
    {
        free(re);
        return NULL;
    }
    j = 0;
    while(j < i)
    {
        re->env[j] = ft_strdup(envp[j]); // create a utils that contain this func
        j++;
    }
    re->env_len = i;
    re->err_code = ER_NO;
    re->free_code = 100;
    re->childn = ft_calloc_norm(1, sizeof(t_child));
    return re;   
}

void read_input(t_data **data)
{
    char *line;
    
    line = readline(PROMPT);
    if (!line)
        handle_eof((*data));
    if(*line)
        add_history(line);
    (*data)->input = line;
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    t_data *data;

    data = init_data(env);
    shlvl(data);
    init_signals();
    while(1)
    {
        read_input(&data);
        data->free_code = NO_FREE;
        if (data->err_code == ER_NO)
            data->tokens = tokenizer(data);
        //if (data->err_code == ER_NO)
        //    data = print(data);
        if (data->err_code == ER_NO)
            data = parser(data);
        if (data->err_code == ER_NO)
           data = execute_token(data);
        free_all(data);
    }
}
