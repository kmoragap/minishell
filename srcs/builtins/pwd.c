/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:34:11 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/04 15:38:14 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_pwd(void)
{
    char *pwd;

    pwd = getcwd(NULL, 0);
    if(!pwd)
        perror("error\n");
    else
    {
        write(1, pwd, ft_strlen(pwd));
        write(1, "\n", 1);
    }
}