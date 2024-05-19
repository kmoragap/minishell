/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:48:53 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/19 12:58:51 by kmoraga          ###   ########.fr       */
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
 * Estas dos variables deben ir actualizando las respectivas variables del env para que cuando alguien...
 * cd ~ y otros casos con argumentos, en ese caso devolver error, pq sería lo más sencillo
*/

void ft_cd(t_data *data)
{
    char *old_pwd;
    char *path;

    old_pwd = getcwd(NULL, 0);
    if (!old_pwd) 
    {
        perror("Failed to get current directory");
        return;
    }
    if (data->tokens->args_num > 0)
    {

        if(ft_strcmp(data->tokens->args[0], "~") == 0)
            path = getenv("HOME");
        else if(ft_strncmp(data->tokens->args[0], "~/", 2) == 0)
            path = ft_strjoin(getenv("HOME"), data->tokens->args[0] + 1);
        else if(ft_strcmp(data->tokens->args[0], "-") == 0)
        {
            path = getenv("OLDPWD");
            write(1, path, ft_strlen(path));
            write(1, "\n", 1);
        }        
        else
            path = data->tokens->args[0];
    }
    else
        path = getenv("HOME");
    
    execute_cd(data, path, old_pwd);
    free(old_pwd);
}

void execute_cd(t_data *data, char *path, char *old_pwd)
{
    char *new_pwd;

    if (chdir(path) != 0) 
    {
        perror("Directory does not exist or cannot be accessed");
        return;
    }
    new_pwd = getcwd(NULL, 0);
    if (!new_pwd) 
    {
        perror("Failed to get new directory");
        return;
    }
    update_env_vars(data, old_pwd, new_pwd);
    free(new_pwd);
}

void update_env_vars(t_data *data, char *old_pwd, char *new_pwd)
{
    char *old;
    char *new;
    size_t old_len;
    size_t new_len;
    
    old_len = ft_strlen("OLDPWD=") + ft_strlen(old_pwd) + 1;
    new_len = ft_strlen("PWD=") + ft_strlen(new_pwd) + 1;
    
    old = ft_calloc_norm(old_len, sizeof(char));
    new = ft_calloc_norm(new_len, sizeof(char));

    if (old == NULL || new == NULL) 
    {
        perror("Failed to allocate memory for environment variables");
        free(old);
        free(new);
        return;
    }

    ft_strcat(old, "OLDPWD=");
    ft_strcat(old, old_pwd);
    ft_strcat(new, "PWD=");
    ft_strcat(new, new_pwd);

    if (replace_var_env(data, old) == 0)
        perror("Error updating OLDPWD");
    if (replace_var_env(data, new) == 0)
        perror("Error updating PWD");

    free(old);
    free(new);
}