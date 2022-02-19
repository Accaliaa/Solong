/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdasser <zdasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:00:51 by zdasser           #+#    #+#             */
/*   Updated: 2022/02/19 14:48:25 by zdasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	char	*p;
	int		i;

	i = 0;
	p = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!p)
		return (0);
	while (src[i] != '\0')
	{
		p[i] = src[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sstr;
	size_t	s_len;
	int		total_alloc_size;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (len - start > s_len)
		total_alloc_size = s_len + 1;
	else
		total_alloc_size = len;
	sstr = (char *)malloc(sizeof(char) * (total_alloc_size + 1));
	if (!sstr)
		return (NULL);
	i = 0;
	while (i < len && s[i] && start < s_len)
	{
		sstr[i] = s[start + i];
		i++;
	}
	sstr[i] = '\0';
	return (sstr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*c;
	size_t	i;
	size_t	j;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	i = ft_strlen(s1) + ft_strlen(s2);
	c = (char *)malloc(sizeof(char) * (i + 1));
	if (!c)
		return (NULL);
	i = -1;
	while (s1[++i])
		c[i] = s1[i];
	j = -1;
	while (s2[++j])
		c[i + j] = s2[j];
	c[i + j] = '\0';
	return (c);
}

int	nl(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
