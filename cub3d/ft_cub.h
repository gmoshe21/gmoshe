/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 19:10:43 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/18 15:01:02 by gmoshe           ###   ########.fr       */
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
# include "libft.h"

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
	int			check;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*sprite;
	int			extension_height;
	int			extension_width;
	int			floor;
	int			ceilling;
	char		*map1;
	char		**map;
	double		myX;
	double		myY;
	int			**sp;
	int			spnum;
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	void		*mlx;
	void		*win;
	int			pixel;
	int			length;
	char		*add;
	void		*img;
	int			endian;
	double		moveSpeed;
	double		rotSpeed;
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
	int		tHeight[5];
	int		tWidth[5];
	int		*texture[5];
	int		drawStart;
	int		drawEnd;
	int		texX;
	double	step;
	double	texPos;
	int		color;
	double	spriteX;
	double	spriteY;
	double	invDet;
	double	transformX;
	double	transformY;
	int		spriteScreenX;
	int		spriteHeight;
	int		drawStartY;
	int		drawEndY;
	int		spriteWidth;
	int		drawStartX;
	int		drawEndX;
}			t_raycast;

void		parsing(char *line, t_cub *cub);
void	raycasting(t_cub *cub);
void	texture_coordinate_stepping(t_cub *cub, t_raycast *rc, int x);
void	movement(t_cub *cub);
int		key_p(int key, t_cub *cub);
int		key_u(int key, t_cub *cub);
void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color);
void	ft_color(t_cub *cub, char *line);
int		frame(t_cub *cub);
void	coordinate_on_the_texture(t_cub *cub, t_raycast *rc);
void	sprites(t_cub *cub, t_raycast *rc, double *ZBuffer);
void	my_map(t_cub *cub);
void	position(t_cub *cub, int x, int y);
int		check(t_cub *cub);
void	valid_floor_ceilling(t_cub *cub, char **str);
void	error_output(int i);
int		close_p(int game, t_cub *cub);

# define CHEK(x) if(!x) return (0);

#endif
