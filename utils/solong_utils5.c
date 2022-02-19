/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdasser <zdasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 14:39:35 by zdasser           #+#    #+#             */
/*   Updated: 2022/02/19 17:15:27 by zdasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../solong.h"
#include "../get_next_line/get_next_line.h"

char	*ftline(char *s)
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

char	*maplenght(int fd)
{
	char		*line;
	char		*tmp;
	static char	*rest;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	check(fd, &rest);
	line = ftline(rest);
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

int	lines_cal(char *name)
{
	int		fd;
	char	*s;
	int		i;
	char	c;

	fd = open(name, O_RDWR);
	s = maplenght(fd);
	i = 0;
	while (s)
	{
		free(s);
		s = maplenght(fd);
		i++;
		if (s)
			c = s[ft_strlen(s) - 1];
	}
	if (c != '1')
	{
		ft_printf("Error\n check the map");
		exit(0);
	}
	close(fd);
	return (i);
}
