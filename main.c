#include "mmlx/mlx.h"
#include "libft/libft.h"
#include <stdlib.h>
#include "get_next_line.h"
#include <stdio.h>
#include "ftprintf/ft_printf.h"

typedef struct	s_data {
	void	*img;
	char	**mat;
	int		size[2];
}	t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	t_data	data;
	int		x;
	int		y;
	int	j, i;
	int		steps;
	t_data img;
}	t_vars;

void mapgenerat(t_vars *vars)
{
	int l;
	int k;
	int	img_width;
	int	img_height;

	l = 0;
	while (l < vars->data.size[0])
	  {
		k = 0;
		vars->i = 0;
		while(k < vars->data.size[1])
		{
			if(vars->data.mat[l][k] == '1')
		 	{
				vars->img.img =  mlx_xpm_file_to_image(vars->mlx, "./wall.xpm", &img_width ,  &img_height);
				mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, k * 80 , l * 80);
			}
			else if (vars->data.mat[l][k] == '0')
			{
			 	vars->img.img =  mlx_xpm_file_to_image(vars->mlx, "./ground.xpm", &img_width ,  &img_height);
				mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, k * 80 , l * 80);
			}
			else if (vars->data.mat[l][k] == 'C')
			{
				vars->img.img =  mlx_xpm_file_to_image(vars->mlx, "./ground.xpm", &img_width ,  &img_height);
				mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, k * 80 , l * 80);
			 	vars->img.img =  mlx_xpm_file_to_image(vars->mlx, "./coin.xpm", &img_width ,  &img_height);
				mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, k * 80 , l * 80);
			}
			else if (vars->data.mat[l][k] == 'P')
			{
				vars->x = l;
				vars->y = k;
			 	vars->img.img =  mlx_xpm_file_to_image(vars->mlx, "./ground.xpm", &img_width ,  &img_height);
				mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, k * 80 , l * 80);
				vars->img.img =  mlx_xpm_file_to_image(vars->mlx, "./player.xpm", &img_width ,  &img_height);
				mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, k * 80 , l * 80);
			}
			else if (vars->data.mat[l][k] == 'E')
			{
			 	vars->img.img =  mlx_xpm_file_to_image(vars->mlx, "./ground.xpm", &img_width ,  &img_height);
				mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, k * 80 , l * 80);
				vars->img.img =  mlx_xpm_file_to_image(vars->mlx, "./exit.xpm", &img_width ,  &img_height);
				mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, k * 80 , l * 80);
			}
			k++;			
		}
	  	l++;
	 }
}

int handlexit(t_vars *vars)
{
	int k;
	int l;

	l = 0;
	while (l < vars->data.size[0])
	{
		k = 0;
		
		while(k < vars->data.size[1])
		{
			if(vars->data.mat[l][k] == 'C')
			{
				ft_printf("please collect all the coins first \n");
				return(0);
			}		
			k++;	
		}
		l++;
	}
	return(1);
}

void steps(t_vars *vars)
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
			exit(0);
	}
}


int	event(int keycode, t_vars *vars)
{
	mlx_clear_window(vars->mlx, vars->win);
	if (keycode == 53)
		exit(0);
	else if (keycode == 2)
		swap(1 , 0, vars);
	else if (keycode == 1)
		swap(0, 1, vars);
	else if (keycode == 0)
		swap(-1, 0, vars);
	else if (keycode == 13)
		swap(0, -1, vars);
	mapgenerat(vars);
	return (0);
}

void	mapcalcul(char *name, t_vars *vars)
{
	int fd;
	
	fd = open(name, O_RDWR);
	char *s;
	vars->data.size[0] = 0;
	s = get_next_line(fd);
	vars->data.size[1] = ft_strlen(s);
	
	while(s)
	{
		free(s);
		vars->data.size[0] += 1;
		s = get_next_line(fd);
	}
	close(fd);
}

void mapread(char *name, t_vars *vars)
{
	char *s;
	int i;
	int fd;

	i = 0;	
	fd = open(name, O_RDWR);
	vars->data.mat = (char **)ft_calloc((vars->data.size[0] + 1), sizeof(char *));
	s = get_next_line(fd);
	
	while (i < vars->data.size[0])
	{
		vars->data.mat[i] = s;
		i++;
		s = get_next_line(fd);
		printf("%s\n", s);
	}
	
}


int	checkexit(t_vars *vars)
{
	int	l;
	int	k;
	int i;

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
	return(i);
}

int	checkcoin(t_vars *vars)
{
	int	l;
	int	k;
	int i;

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
	return(i);
}



int	checkplayer(t_vars *vars)
{
	int	l;
	int	k;
	int i;

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
	return(i);
}

int	checkwalls(t_vars *vars)
{
	int	l;
	int	k;

	l = 0;
	while (l < vars->data.size[0])
	{
		k = 0;
		while (k < vars->data.size[1])
		{
			if (vars->data.mat[0][k] != '1' || vars->data.mat[vars->data.size[0] - 1][k] != '1')
				return(0);
			if (vars->data.mat[l][0] != '1' || vars->data.mat[l][vars->data.size[1] - 1] != '1')
				return(0);
			if ((size_t)vars->data.size[1] != ft_strlen(vars->data.mat[l]))
				return (0);
			k++;	
		}
	  	l++;
	 } 
	return(1);
}

int	maperror(t_vars *vars)
{
	
	if(!checkwalls(vars))
	{
		ft_printf("Error map : check the walls \n");
		return(0);
	}
	if(checkplayer(vars) > 1 || checkplayer(vars) == 0 )
	{
		ft_printf("Error map : check the Player \n");
		return(0);
	}
	if(!checkexit(vars))
	{
		ft_printf("Error map : check the exit \n");
		return(0);
	}
	if(!checkcoin(vars))
	{
		ft_printf("Error map : check the walls \n");
		return(0);
	}
	return(1);
}

int	main(int argc, char **argv)
{
	t_vars vars;
	int		l;
	char *map;

	(void)argc;
	l = 0;
	vars.j = 0;
	map = argv[1];
	vars.steps = 0;
	mapcalcul(map, &vars);
	mapread(map, &vars);
	if(!maperror(&vars))
		return(0);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.data.size[1]*80, vars.data.size[0]*80, "solong");
	mapgenerat(&vars);
	mlx_key_hook(vars.win, event, &vars);
	mlx_loop(vars.mlx);
}
