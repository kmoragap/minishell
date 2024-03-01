/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:25:00 by kmoraga           #+#    #+#             */
/*   Updated: 2024/02/29 11:49:24 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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