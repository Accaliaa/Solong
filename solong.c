/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdasser <zdasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 17:37:31 by zdasser           #+#    #+#             */
/*   Updated: 2022/02/19 18:21:17 by zdasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	mapgenerat(t_vars *vars)
{
	int	l;
	int	k;

	l = 0;
	while (l < vars->data.size[0])
	{
		k = 0;
		while (k < vars->data.size[1])
		{
			put_imgs(vars, k, l);
			k++;
		}
		l++;
	}
}

int	maperror(t_vars *vars)
{
	if (!checksize(vars))
		return (0);
	if (!checkwalls(vars))
	{
		ft_printf("Error \n check the walls \n");
		return (0);
	}
	if (checkplayer(vars) != 1)
	{
		ft_printf("Error \n check the Player \n");
		return (0);
	}
	if (!checkexit(vars))
	{
		ft_printf("Error \n check the exit \n");
		return (0);
	}
	if (!checkcoin(vars))
	{
		ft_printf("Error \n check the walls \n");
		return (0);
	}
	return (1);
}

int	mapcheck(char *name)
{
	int	fd;

	fd = open(name, O_RDWR);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	argcheck(int argc, t_vars *vars, char *str)
{
	if (argc != 2)
	{
		ft_printf("Error \n arguments not valid \n");
		return (0);
	}
	vars->j = 0;
	vars->steps = 0;
	if (!mapcheck(str))
	{
		ft_printf("Error \n the map should exist \n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argcheck(argc, &vars, argv[1]) == 0)
		return (0);
	mapcalcul(argv[1], &vars);
	if (!mapread(argv[1], &vars) || !checkchar("PEC01", &vars) || \
			!maperror(&vars) || !ext_check(".ber", argv[1]))
		return (0);
	if (lines_cal(argv[1]) != vars.data.size[0])
		return (0);
	initimage(&vars);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window (vars.mlx, vars.data.size[1] * 80,
			vars.data.size[0] * 80, "solong");
	mapgenerat(&vars);
	mlx_key_hook(vars.win, event, &vars);
	mlx_hook(vars.win, 17, (1L << 5), closewindow, NULL);
	mlx_loop(vars.mlx);
}
