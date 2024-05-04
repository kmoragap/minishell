/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:19:13 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/04 15:21:51 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void put_env(t_data *data)
{
    int i;

    i = 0;

    while(i < data->env_len)
    {
        //aqui debe mandar algo al stdo
        printf("%s\n", data->env[i]);
        i++;
    }
    
}