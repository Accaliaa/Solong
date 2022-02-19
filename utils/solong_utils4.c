/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdasser <zdasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:09:59 by zdasser           #+#    #+#             */
/*   Updated: 2022/02/19 09:16:17 by zdasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../solong.h"

int	checkplayer(t_vars *vars)
{
	int	l;
	int	k;
	int	i;

	i = 0;
	l = 0;
	while (l < vars->data.size[0])
	{
		k = 0;
		while (k < vars->data.size[1])
		{
			if (vars->data.mat[l][k] == 'P')
				i++;
			k++;
		}
		l++;
	}
	return (i);
}

int	ext_check(char *c, char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
		i++;
	i = i - 3;
	while (j++ < 4)
	{
		if (c[j] != s[i])
		{
			ft_printf("error : check extension");
			return (0);
		}
		i++;
	}
	return (1);
}

void	mapcalcul(char *name, t_vars *vars)
{
	int		fd;
	char	*s;

	fd = open(name, O_RDWR);
	vars->data.size[0] = 0;
	s = get_next_line(fd);
	vars->data.size[1] = ft_strlen(s);
	while (s)
	{
		free(s);
		vars->data.size[0]++;
		s = get_next_line(fd);
	}
	ft_printf("hna : %d \n", vars->data.size[0]);
	close(fd);
}

int	closewindow(void)
{
	exit(0);
	return (0);
}

int	checksize(t_vars *vars)
{
	int	size;
	int	i;

	i = 0;
	size = ft_strlen(vars->data.mat[0]);
	while (i < vars->data.size[0])
	{
		if (size != (int)ft_strlen(vars->data.mat[i]))
			return (0);
		i++;
	}
	return (1);
}
