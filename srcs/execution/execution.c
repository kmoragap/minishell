/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creuther <creuther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:35:50 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/10 16:34:11 by creuther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_data  *execute_token(t_data *data)
{
    data = piping(data);
    if (data->err_code != ER_NO)
      return (data);
    data = create_children(data);
    return (data);
}
