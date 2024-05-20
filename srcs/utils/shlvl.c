/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:50:34 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/20 12:15:47 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shlvl(t_data *data)
{
	char	*level;
	char	*new_shlvl;
	size_t	new_len;
	int		nb_lvl;

	nb_lvl = 1;
	level = getenv("SHLVL");
	new_len = ft_strlen("SHLVL=") + ft_strlen(level) + 1;
	new_shlvl = ft_calloc_norm(new_len, sizeof(char));
	if (level != NULL)
	{
		nb_lvl = ft_atoi(level) + 1;
		level = ft_itoa(nb_lvl);
	}
	else
	{
		nb_lvl = 1;
		level = ft_itoa(nb_lvl);
	}
	ft_strcat(new_shlvl, "SHLVL=");
	ft_strcat(new_shlvl, level);
	// write(1, new_shlvl, ft_strlen(new_shlvl));
	// write(1, "\n", 1);
	if (replace_var_env(data, new_shlvl) == 0)
		write(2, "Error updating SHLVL", 21);
	free(level);
	free(new_shlvl);
}
