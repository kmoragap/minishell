/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creuther <creuther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2022/12/26 12:04:51 by creuther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*base[4096];
	char		*newstr;
	int			len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	base[fd] = ft_read(base[fd], fd);
	if (base[fd] == NULL)
		return (NULL);
	len = ft_strlen_nl_end(base[fd]);
	newstr = ft_strdup_a(base[fd], len);
	base[fd] = ft_new_base(base[fd], len);
	return (newstr);
}

char	*ft_read(char *base, int fd)
{
	char	*buffer;
	int		iend;

	iend = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (iend > 0 && ft_strchr_null(base, '\n') == 0)
	{
		iend = read(fd, buffer, BUFFER_SIZE);
		if (iend == -1)
		{	
			free(buffer);
			free(base);
			return (NULL);
		}
		buffer[iend] = '\0';
		base = ft_strjoin(base, buffer);
	}
	free(buffer);
	return (base);
}

int	ft_strlen_nl_end(char *base)
{
	int	len;

	len = 0;
	while (base[len] != '\0' && base[len] != '\n')
		len++;
	return (len);
}

char	*ft_strdup_a(char *src, int len)
{
	char	*dest;
	int		i;

	i = 0;
	if (!src[0])
		return (NULL);
	if (src[len] == '\n')
		len++;
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	while (src[i] != '\0' && i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
