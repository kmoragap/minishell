/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creuther <creuther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/10 17:25:02 by creuther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    input_error(t_data *data, t_free code, int exit_code, char *txt)
{
    data->err_code = ER_INPUT;
    data->free_code = code;
    data->exit_code = exit_code;
    perror(txt);
}

void    malloc_error(t_data *data, t_free code)
{
    data->free_code = code;
    data->err_code = ER_MALLOC;
    data->exit_code = 12;
    perror("Error: malloc failure");
}
