/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:38:23 by kmoraga           #+#    #+#             */
/*   Updated: 2024/04/16 12:14:41 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data *init_data(char **envp)
{
    t_data *re;
    int i;
    int j;

    re = malloc(sizeof(t_data));
    if (!re)
        return (NULL);
    re->env_len = 0;
    re->input = NULL;
    i = 0;
    while(envp[i])
        i++;
    re->env = malloc(sizeof(char *) * (i + 2));
    if (!re->env)
    {
        free(re);
        return (NULL);
    }
    j = 0;
    while(j < i)
    {
        re->env[j] = ft_strdup(envp[j]); // create a utils that contain this func
        j++;
    }
    re->env[j] = ft_strdup(" "); // cadena vacia para el prompt 
    re->env[j + 2] = NULL; // caracter nulo al final
    re->env_len = i + 2;
    re->err_code = ER_NO;
    re->free_code = NO_FREE;
    re->childn = ft_calloc_norm(1, sizeof(t_child));
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
        if (data->err_code == ER_NO)
           data = execute_token(data);
        if (data->err_code == ER_NO)
            data = print(data);
        printf("input done\n");
        free_all(data);
    }
}
