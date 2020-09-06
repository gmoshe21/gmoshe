/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 19:10:43 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/05 16:41:44 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB_H
# define FT_CUB_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "mlx.h"

typedef struct	s_cub
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*sprite;
	int		extension_height;
	int		extension_width;
	char	**floor;
	char	**ceilling;
	char	*map1;
	char	**map;
	int		myX;
	int		myY;
	int		spX;
	int		spY;
	int		w;
	int		a;
	int		s;
	int		d;
	int		dirX;
	int		dirY;
	int		planeX;
	int		planeY;
	void	*mlx;
	void	*win;
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
}			t_raycast;

void	parsing(char *line, t_cub *cub);

#endif
