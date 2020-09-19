/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 19:10:43 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/19 13:53:54 by gmoshe           ###   ########.fr       */
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
	double		myx;
	double		myy;
	int			**sp;
	int			spnum;
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	void		*mlx;
	void		*win;
	int			pixel;
	int			length;
	char		*add;
	void		*img;
	int			endian;
	double		movespeed;
	double		rotspeed;
	int			theight[5];
	int			twidth[5];
	int			*texture[5];
}				t_cub;

typedef struct	s_raycast
{
	double		camerax;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;
	int			hit;
	int			side;
	int			stepx;
	int			stepy;
	int			lineheight;
	// int			theight[5];
	// int			twidth[5];
	// int			*texture[5];
	int			drawstart;
	int			drawend;
	int			texx;
	double		step;
	double		texpos;
	int			color;
	double		spritex;
	double		spritey;
	double		invdet;
	double		transformx;
	double		transformy;
	int			spritescreenx;
	int			spriteheight;
	int			drawstarty;
	int			drawendy;
	int			spritewidth;
	int			drawstarts;
	int			drawendx;
}				t_raycast;

void			parsing(char *line, t_cub *cub);
void			raycasting(t_cub *cub);
void			texture_coordinate_stepping(t_cub *cub, t_raycast *rc, int x);
void			movement(t_cub *cub);
int				key_p(int key, t_cub *cub);
int				key_u(int key, t_cub *cub);
void			my_mlx_pixel_put(t_cub *cub, int x, int y, int color);
void			ft_color(t_cub *cub, char *line);
int				frame(t_cub *cub);
void			coordinate_on_the_texture(t_cub *cub, t_raycast *rc);
void			sprites(t_cub *cub, t_raycast *rc, double *zbuffer);
void			my_map(t_cub *cub);
void			position(t_cub *cub, int x, int y);
int				check(t_cub *cub);
void			valid_floor_ceilling(t_cub *cub, char **str);
void			error_output(int i);
int				close_p(int game, t_cub *cub);
void	scrin_bmp(t_cub *cub);
int i(int x);
void	chek_scrin(t_cub *cub, char *argv);

# define CHEK(x) if(!x) return (0);

#endif
