/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdasser <zdasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:07:35 by zdasser           #+#    #+#             */
/*   Updated: 2022/02/19 17:06:08 by zdasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../solong.h"

int	checkwalls(t_vars *vars)
{
	int	l;
	int	k;

	l = -1;
	while (++l < vars->data.size[0])
	{
		k = -1;
		while (++k < vars->data.size[1])
		{
			if (vars->data.mat[0][k] != '1' || \
				vars->data.mat[vars->data.size[0] - 1][k] != '1' || \
				vars->data.mat[l][0] != '1' || \
				vars->data.mat[l][vars->data.size[1] - 1] != '1' || \
				vars->data.size[1] != ft_strlen(vars->data.mat[l]))
			{
				return (0);
			}
		}
	}
	return (1);
}

int	checkchar(char *s, t_vars *vars)
{
	int	l;
	int	k;

	k = 0;
	l = 0;
	while (l < vars->data.size[0])
	{
		k = 0;
		while (k < vars->data.size[1])
		{
			if (!ft_strchr(s, vars->data.mat[l][k]))
			{
				ft_printf("Error\n check map \n");
				return (0);
			}
			k++;
		}
		l++;
	}
	return (1);
}

int	checkexit(t_vars *vars)
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
			if (vars->data.mat[l][k] == 'E')
				i++;
			k++;
		}
		l++;
	}
	return (i);
}

int	checkcoin(t_vars *vars)
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
			if (vars->data.mat[l][k] == 'C')
				i++;
			k++;
		}
		l++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}
