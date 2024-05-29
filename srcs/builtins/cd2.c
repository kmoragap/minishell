/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:48:53 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/27 15:48:18 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_concat(char *old, char *old_pwd)
{
	ft_strcat(old, "OLDPWD=");
	ft_strcat(old, old_pwd);
	return (old);
}

void	free_old_new(char *old, char *new)
{
	free(old);
	free(new);
}

void	update_env_vars(t_data *data, char *old_pwd, char *new_pwd)
{
	char	*old;
	char	*new;
	size_t	old_len;
	size_t	new_len;

	old_len = ft_strlen("OLDPWD=") + ft_strlen(old_pwd) + 1;
	new_len = ft_strlen("PWD=") + ft_strlen(new_pwd) + 1;
	old = ft_calloc_norm(old_len, sizeof(char));
	new = ft_calloc_norm(new_len, sizeof(char));
	if (old == NULL || new == NULL)
	{
		malloc_error(data, F_PIDS);
		if (old)
			free(old);
		return ;
	}
	old = ft_concat(old, old_pwd);
	ft_strcat(new, "PWD=");
	ft_strcat(new, new_pwd);
	if (replace_var_env(data, old) == 0)
		return (free_old_new(old, new));
	if (replace_var_env(data, new) == 0)
		return (free_old_new(old, new));
	return (free_old_new(old, new));
}
