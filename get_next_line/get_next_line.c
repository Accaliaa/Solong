/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdasser <zdasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:59:48 by zdasser           #+#    #+#             */
/*   Updated: 2022/02/19 09:15:34 by zdasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_getrest(char *s)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (ft_substr(s, i + 1, ft_strlen(s)));
		i++;
	}
	return (ft_strdup(""));
}

char	*ft_getline(char *s)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (ft_substr(s, 0, i + 1));
		i++;
	}
	return (ft_strdup(s));
}

void	check(int fd, char **rest)
{
	int		j;
	char	*tmp;
	char	*buff;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (!nl(*rest))
	{
		j = read(fd, buff, BUFFER_SIZE);
		if (j <= 0)
			break ;
		else
		{
			buff[j] = '\0';
			tmp = *rest;
			*rest = ft_strjoin(*rest, buff);
			free(tmp);
		}
	}
	free(buff);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*tmp;
	static char	*rest;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	check(fd, &rest);
	line = ft_getline(rest);
	tmp = rest;
	rest = ft_getrest(rest);
	free(tmp);
	if (line == NULL || rest == NULL)
	{
		free(line);
		free(rest);
		return (NULL);
	}
	if (*rest == '\0' && *line == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
