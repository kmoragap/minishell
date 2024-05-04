/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:38:23 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/04 13:00:31 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data *init_data(char **envp)
{
    t_data *re;
    int i;
    int j;

    re = NULL;
    if(ft_calloc(re, ER_SHUTDOWN, (void *)&re, sizeof(t_data)) == 1)
        return NULL;
    re->env_len = 0;
    re->input = NULL;
    i = 0;
    while(envp[i])
        i++;
    if(ft_calloc(re, ER_SHUTDOWN, (void *)&re->env, (sizeof(char *) * (i + 2))) == 1)
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
    re->env[j + 1] = NULL; // caracter nulo al final
    re->env_len = i + 1;
    re->err_code = ER_NO;
    re->free_code = NO_FREE;

    for(int s = 0; s < (re->env_len + 1); s++)
        printf("env: %s\n", re->env[s++]);
    return re;   
}

void read_input(t_data **data)
{
    char *line;
    
    line = readline(PROMPT);
    if (!line)
        (*data)->err_code = ER_MALLOC;
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
    while(1)
    {
        read_input(&data);
        printf("input: %s\n", data->input);
        if (data->err_code == ER_NO)
            data->tokens = tokenizer(data);
        if (data->err_code == ER_NO)
            data = parser(data);
        if(data->err_code == ER_NO)
            execute_token(data);
        printf("env_len: %d\n", data->env_len);
        if (data->err_code == ER_NO)
            data = print(data);
        printf("input done\n");
        free_all(data);
        for(int s = 0; s < data->env_len; s++)
            printf("env: %s\n", data->env[s++]);
        printf("env_len: %d\n", data->env_len);
    }
}
