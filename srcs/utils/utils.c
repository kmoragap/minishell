/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:34:26 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/19 16:28:02 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isascii(int c)
{
	return ((c >= 0 && c <= 127));
}

int	ft_isdigit(int c)
{
	return ((c >= 48 && c <= 57));
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	else
		return (0);
}

static int	f_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		len++;
		n = -n;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	int		num;
	char	*s;

	len = f_len(n);
	num = n;
	s = (char *)ft_calloc_norm(1, (sizeof(char) * len) + 1);
	if (s == NULL)
		return (NULL);
	s[len] = '\0';
	if (num == 0)
		s[0] = '0';
	if (num < 0)
	{
		s[0] = '-';
		num = -num;
	}
	while (num)
	{
		s[--len] = num % 10 + '0';
		num /= 10;
	}
	return (s);
}

char	*ft_strdup(char *src)
{
	char	*dest;

	dest = (char *)ft_calloc_norm(1, ft_strlen((char *)src) + 1);
	if (!dest)
		return (NULL);
	dest = ft_strcpy((char *)src, dest);
	return (dest);
}

char	*ft_strndup(char *src, int len)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	while(i < len && src[i])
    {
        dest[i] = src[i];
        i++;
    }
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcpy(char *src, char *dest)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int		ft_calloc(t_data *data, t_free code, void **arr, size_t size)
{
	*arr = ft_calloc_norm(1, size);
	if (!(*arr))
	{
		*arr = NULL;
		malloc_error(data, code);
		return (1);
	}
	ft_bzero(*arr, size);
	return (0);
}

void	*ft_calloc_norm(size_t n, size_t size)
{
	size_t	i;
	void	*arr;

	i = n * size;
	arr = (void *) malloc (i);
	if (arr == NULL)
		return (NULL);
	ft_bzero(arr, i);
	return (arr);
}

void	ft_bzero(void *str, size_t n)
{
	unsigned char	*c;
	size_t			i;

	c = str;
	i = 0;
	while (i < n)
	{
		*c = '\0';
		i++;
		c++;
	}
}

t_token	*move_to_first_token(t_token *token)
{
	while (token->prev)
		token = token->prev;
	return (token);
}

int	ft_strchr(const char *str, int c)
{
	while (c > 127)
		c = c - 128;
	while (*str)
	{
		if (c == *str)
			return (0);
		str++;
	}
	if (c == '\0')
		return (1);
	return (1);
}

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	while (c > 127)
		c = c - 128;
	i = 0;
	while (str[i] != '\0')
		i++;
	while (i >= 0)
	{	
		if (str[i] == c)
			return ((char *) &str[i]);
		i--;
	}
	return (NULL);
}

char	*ft_strnjoin(char *s1, char *s2, int len2)
{
	char	*new;
	size_t	len;

	len = ft_strlen((char *)s1) + len2;
	new = (char *)malloc(len + 1);
	if (new == NULL)
		return (NULL);
	ft_memcpy((void *)new, (const void *)s1, ft_strlen((char *)s1));
	ft_memmove((void *)(new + ft_strlen((char *)s1)),
		(const void *)s2, len2);
	new[len] = '\0';
	free(s1);
	return (new);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	len;

	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	new = (char *)malloc(len + 1);
	if (new == NULL)
		return (NULL);
	ft_memcpy((void *)new, (const void *)s1, ft_strlen((char *)s1));
	ft_memmove((void *)(new + ft_strlen((char *)s1)),
		(const void *)s2, ft_strlen((char *)s2));
	new[len] = '\0';
	return (new);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*s;
	char		*d;
	size_t		i;

	i = 0;
	d = dest;
	s = src;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		*d = *s;
		s++;
		d++;
		i++;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*s;
	char		*d;
	size_t		i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	d = dest;
	s = src;
	while (i < n)
	{
		if (s < d)
			d[n - 1 - i] = s[n - 1 - i];
		else
			d[i] = s[i];
		i++;
	}
	return (dest);
}

int is_valid_expand_var(char *str, int c)
{
	int i;

	i = 0;

	while(str[i])
	{
		if(str[i] == c)
			return 1;
		i++;
	}
	return 0;
}

char *ft_strcat(char *dest, const char *src) 
{
    int i;
    int j;

    i = 0;
    while (dest[i] != '\0')
        i++;

    j = 0;
    
    while (src[j] != '\0')
    {
        dest[i] = src[j];
        i++;
        j++;
    }

    dest[i] = '\0';

    return dest;
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && (i < n))
	{
		if (s1[i] != s2[i])
		{
			return (((unsigned char)s1[i] - (unsigned char)s2[i]));
		}
		i++;
	}
	if (i != n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}