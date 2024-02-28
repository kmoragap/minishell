/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:25:00 by kmoraga           #+#    #+#             */
/*   Updated: 2024/02/28 22:25:20 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void read_input(t_data **data)
{
    char *line;
    
    line = readline(PROMPT);
    
    //alloc struct
    if(*line)
        add_history(line);
    (*data)->input = line;

}