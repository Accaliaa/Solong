/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdasser <zdasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 21:34:45 by zdasser           #+#    #+#             */
/*   Updated: 2022/02/19 16:31:34 by zdasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H

# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include "get_next_line/get_next_line.h"
# include "ftprintf/ft_printf.h"

typedef struct s_data {
	void	*wall;
	void	*ground;
	void	*player;
	void	*coin;
	void	*exit;
	char	**mat;
	int		size[2];
}	t_data;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	t_data	data;
	int		x;
	int		y;
	int		j;
	int		i;
	int		steps;
	char	*name;
	t_data	img;
}	t_vars;

void	initimage(t_vars	*vars);
void	mapgenerat(t_vars	*vars);
int		handlexit(t_vars	*vars);
void	steps(t_vars *vars);
void	swap(int i, int j, t_vars *vars);
int		event(int keycode, t_vars *vars);
void	mapcalcul(char *name, t_vars *vars);
int		mapread(char *name, t_vars *vars);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		checksize(t_vars *vars);
int		ext_check(char *c, char *s);
char	*ft_strchr(const char *s, int c);
int		checkchar(char *s, t_vars *vars);
void	put_imgs(t_vars *vars, int x, int y);
int		checkwalls(t_vars *vars);
int		checkplayer(t_vars *vars);
int		checkexit(t_vars *vars);
int		checkcoin(t_vars *vars);
int		closewindow(void);
int		lines_cal(char *name);

#endif
