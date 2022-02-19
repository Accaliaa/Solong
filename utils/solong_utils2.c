/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdasser <zdasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 21:34:54 by zdasser           #+#    #+#             */
/*   Updated: 2022/02/16 21:32:42 by zdasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../solong.h"

int	event(int keycode, t_vars *vars)
{
	mlx_clear_window(vars->mlx, vars->win);
	if (keycode == 53)
		exit(0);
	else if (keycode == 2)
		swap(1, 0, vars);
	else if (keycode == 1)
		swap(0, 1, vars);
	else if (keycode == 0)
		swap(-1, 0, vars);
	else if (keycode == 13)
		swap(0, -1, vars);
	mapgenerat(vars);
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	while (n--)
		((char *)s)[n] = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = (void *)malloc(count * size);
	if (!p)
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}

void	initimage(t_vars	*vars)
{
	int	img_width;
	int	img_height;

	vars->img.wall = mlx_xpm_file_to_image(vars->mlx,
			"assets/wall.xpm",
			&img_width, &img_height);
	vars->img.ground = mlx_xpm_file_to_image(vars->mlx,
			"assets/ground.xpm",
			&img_width, &img_height);
	vars->img.coin = mlx_xpm_file_to_image(vars->mlx,
			"assets/coin.xpm",
			&img_width, &img_height);
	vars->img.exit = mlx_xpm_file_to_image(vars->mlx,
			"assets/exit.xpm",
			&img_width, &img_height);
	vars->img.player = mlx_xpm_file_to_image(vars->mlx,
			"assets/player.xpm",
			&img_width, &img_height);
}

int	mapread(char *name, t_vars *vars)
{
	char	*s;
	int		i;
	int		fd;

	i = 0;
	fd = open(name, O_RDWR);
	vars->data.mat = (char **)ft_calloc((vars->data.size[0] + 1),
			sizeof(char *));
	s = get_next_line(fd);
	while (i < vars->data.size[0])
	{
		ft_printf("s = %s\n", s);
		if (!s)
			return (0);
		vars->data.mat[i] = s;
		i++;
		s = get_next_line(fd);
	}
	return (1);
}
