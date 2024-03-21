/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:38:23 by kmoraga           #+#    #+#             */
/*   Updated: 2024/03/15 14:43:41 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_data *init_data(char **envp)
{
    t_data *re;
    int i;
    int j;

    re = malloc(sizeof(t_data));
    re->env_len = 0;
    re->input = NULL;

    i = 0;
    while(envp[i])
        i++;
    re->env = malloc(sizeof(char *) * (i + 2));
    j = 0;
    while(j < i)
    {
        re->env[j] = strdup(envp[j]); // create a utils that contain this func
        j++;
    }
    re->env[j +1] = NULL; // cadena vacia para el prompt 
    re->env_len = i + 1;
    return re;   
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
        lexer(&data);
        parser(&data);
    }
}