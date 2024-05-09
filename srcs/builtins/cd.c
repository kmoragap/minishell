/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:48:53 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/09 09:17:50 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Necesito cambiar el directorio de PWD
 * Necesito cambiar el OLDPWD:
 * home/kris --> cd --> home/kris/desktop
 * PWD = home/kris/desktop
 * OLDPWD = home/kris/
 * home/kris/desktop --> cd --> home/kris/desktop/example_folder
 * PWD = home/kris/desktop/example_folder
 * OLDPWD = home/kris/desktop/
 * Usar chdir para ir a la sig. carpeta 
 * Manejar los errores cuando no se encuentre la carpeta:
 *  - The directory specified in path does not exist
 *  - failed to get new directory
 *  - failed to change the directory
 *  - failed to get current directory
 * Si se usa solo cd usar getcwd para obtener HOME y establecerlo, ya que eso hace por default
 * Se podría usar getcwd para actualizar el valor de la variable PWD en el env, y también para guardar el old_pwd en otra variable para así actualizar el PWD
 * Estas dos variables deben ir actualizando las respectivas variables del env para que cuando alguien hag a
*/


void ft_cd(t_data *data)
{
    return ;
}