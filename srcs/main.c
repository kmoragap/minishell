/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:38:23 by kmoraga           #+#    #+#             */
/*   Updated: 2024/04/05 17:37:33 by codespace        ###   ########.fr       */
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
    re->env[j] = strdup(" "); // cadena vacia para el prompt 
    re->env[j + 2] = NULL; // caracter nulo al final
    re->env_len = i + 2;
    return re;   
}

void read_input(t_data **data)
{
    char *line;
    
    line = readline(PROMPT);
    
    //alloc struct
    if(*line)
        add_history(line);
    (*data)->input = line;
/*  
    for(int i = 0; i < dt->env_len; i++)
        printf("env %d: %s\n",i, dt->env[i]);
*/

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
        tokenizer(&data);
        //lexer(&data);
        //parse_input(&data);
        //print_dot(data->node);
    }
}