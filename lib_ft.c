/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 00:05:30 by esamad-j          #+#    #+#             */
/*   Updated: 2023/06/24 14:35:45 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == '\0')
	{
		return ((char *)haystack);
	}
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && haystack[i + j] != '\0' && i
			+ j < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)&haystack[i]);
			j++;
		}
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	cont;

	cont = 0;
	while (s[cont] != '\0')
		cont++;
	return (cont);
}

char	*ft_strjoin(char const *str1, char const *str2)
{
	int		i;
	int		j;
	char	*new_str;
	size_t	new_len;

	i = 0;
	j = 0;
	new_len = (ft_strlen(str1) + ft_strlen(str2));
	new_str = malloc(sizeof(char) * (new_len + 1));
	if (!new_str)
		return (0);
	while (str1[i] != '\0')
	{
		new_str[i] = str1[i];
		i++;
	}
	while (str2[j] != '\0')
	{
		new_str[i] = str2[j];
		i++;
		j++;
	}
	new_str[i] = 0;
	return (new_str);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s != '\0')
	{
		write(fd, s, 1);
		s++;
	}
}

char	*ft_strdup(char *src)
{
	int		i;
	int		j;
	char	*src_with_memory;

	i = 0;
	j = 0;
	i = ft_strlen(src);
	src_with_memory = (char *)malloc(i * sizeof(char) + 1);
	if (src_with_memory == NULL)
		return (0);
	while (src[j] != '\0')
	{
		src_with_memory[j] = src[j];
		j++;
	}
	src_with_memory[j] = '\0';
	return (src_with_memory);
}
