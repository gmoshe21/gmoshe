/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 19:10:43 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/08 13:17:13 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB_H
# define FT_CUB_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "mlx.h"
# include <math.h>

enum
{
	key_A = 0x00,
	key_D = 0x02,
	key_S = 0x01,
	key_W = 0x0D,
	key_left = 0x7B,
	key_right = 0x7C,
};

typedef struct	s_cub
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*sprite;
	int		extension_height;
	int		extension_width;
	int		floor;
	int		ceilling;
	char	*map1;
	char	**map;
	double		myX;
	double		myY;
	int		spX;
	int		spY;
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
	int		dirX;
	int		dirY;
	int		planeX;
	int		planeY;
	void	*mlx;
	void	*win;
	int		pixel;
	int		length;
	char	*add;
	void	*img;
	int		endian;
}			t_cub;

typedef struct	s_raycast
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		hit;
	int		side;
	int		stepX;
	int		stepY;
	int		lineHeight;
	int		tHeight[4];
	int		tWidth[4];
	int		*texture[4];
	int		drawStart;
	int		drawEnd;
	int		texX;
	double	step;
	double	texPos;
	int		color;
	double	moveSpeed;
	double	rotSpeed;
}			t_raycast;

void	parsing(char *line, t_cub *cub);
void	raycasting(t_cub *cub, t_raycast *rc);
void	texture_coordinate_stepping(t_cub *cub, t_raycast *rc, int x);
void	movementrayd(t_cub *cub, t_raycast *rc);
int		key_p(int key, t_cub *cub);
int		key_u(int key, t_cub *cub);
void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color);
void	ft_color(t_cub *cub, char *line);
int		draw_frame(t_cub *cub, t_raycast *rc);

#endif
