/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creuther <creuther@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/04/05 17:36:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    input_error(t_data *data, t_free code, char *txt)
{
    data->err_code = ER_INPUT;
    data->free_code = code;
    printf("%s", txt);
}

void    malloc_error(t_data *data, t_free code)
{
    data->free_code = code;
    data->err_code = ER_MALLOC;
    printf("Error: malloc failure\n");
}
