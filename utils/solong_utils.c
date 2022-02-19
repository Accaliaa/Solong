/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdasser <zdasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 21:08:33 by zdasser           #+#    #+#             */
/*   Updated: 2022/02/19 18:22:38 by zdasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../solong.h"

void	img(t_vars *vars, void *img, int x, int y)
{
	mlx_put_image_to_window(vars->mlx, vars->win, img, x, y);
}

void	put_imgs(t_vars *vars, int x, int y)
{
	if (vars->data.mat[y][x] == '1')
		img(vars, vars->img.wall, x * 80, y * 80);
	else if (vars->data.mat[y][x] == '0')
		img(vars, vars->img.ground, x * 80, y * 80);
	else if (vars->data.mat[y][x] == 'C')
	{
		img(vars, vars->img.ground, x * 80, y * 80);
		img(vars, vars->img.coin, x * 80, y * 80);
	}
	else if (vars->data.mat[y][x] == 'P')
	{
		vars->x = y;
		vars->y = x;
		img(vars, vars->img.ground, x * 80, y * 80);
		img(vars, vars->img.player, x * 80, y * 80);
	}
	else if (vars->data.mat[y][x] == 'E')
	{
		img(vars, vars->img.ground, x * 80, y * 80);
		img(vars, vars->img.exit, x * 80, y * 80);
	}
}

int	handlexit(t_vars *vars)
{
	int	k;
	int	l;

	l = 0;
	while (l < vars->data.size[0])
	{
		k = 0;
		while (k < vars->data.size[1])
		{
			if (vars->data.mat[l][k] == 'C')
			{
				ft_printf("Error \n please collect all the coins first \n");
				return (0);
			}
			k++;
		}
		l++;
	}
	return (1);
}

void	steps(t_vars *vars)
{
	vars->steps++;
	ft_printf("number of steps : %i \n", vars->steps);
}

void	swap(int i, int j, t_vars *vars)
{
	if (vars->data.mat[vars->x + j][vars->y + i] == '0')
	{
		vars->data.mat[vars->x][vars->y] = '0';
		vars->data.mat[vars->x + j][vars->y + i] = 'P';
		steps(vars);
	}
	if (vars->data.mat[vars->x + j][vars->y + i] == 'C')
	{
		vars->data.mat[vars->x][vars->y] = '0';
		vars->data.mat[vars->x + j][vars->y + i] = 'P';
		steps(vars);
	}
	if (vars->data.mat[vars->x + j][vars->y + i] == 'E')
	{
		if (handlexit(vars))
		{
			steps(vars);
			exit(0);
		}
	}
}
