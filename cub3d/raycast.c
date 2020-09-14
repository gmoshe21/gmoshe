/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 16:07:37 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/14 17:55:44 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	coordinate_on_the_texture(t_cub *cub, t_raycast *rc)
{
	double	wallx;

	if (rc->side == 0)
		wallx = cub->myY + rc->perpWallDist * rc->rayDirY;
	else
		wallx = cub->myX + rc->perpWallDist * rc->rayDirX;
	wallx -= floor((wallx));
	if (rc->side == 0)
	{
		if (rc->stepX < 0)
			rc->texX = (int)(wallx * (double)(rc->tWidth[0]));
		else
			rc->texX = (int)(wallx * (double)(rc->tWidth[1]));
	}
	else
	{
		if (rc->stepY < 0)
			rc->texX = (int)(wallx * (double)(rc->tWidth[2]));
		else
			rc->texX = (int)(wallx * (double)(rc->tWidth[3]));
	}
	if (rc->side == 0 && rc->rayDirX < 0)
		rc->texX = rc->tWidth[0] - rc->texX - 1;
	if (rc->side == 0 && rc->rayDirX > 0)
		rc->texX = rc->tWidth[1] - rc->texX - 1;
}

void	next2(t_cub *cub, t_raycast *rc, int x, int i)
{
	int	texy;

	if (rc->stepY < 0)
	{
		texy = (int)rc->texPos & (rc->tHeight[2] - 1);
		rc->color = rc->texture[2][rc->tHeight[2] * texy + rc->texX];
		my_mlx_pixel_put(cub, x, i, rc->color);
	}
	else
	{
		texy = (int)rc->texPos & (rc->tHeight[3] - 1);
		rc->color = rc->texture[3][rc->tHeight[3] * texy + rc->texX];
		my_mlx_pixel_put(cub, x, i, rc->color);
	}
}

void	next(t_cub *cub, t_raycast *rc, int x, int i)
{
	int		texy;

	rc->texPos += rc->step;
	if (rc->side == 0)
	{
		if (rc->stepX < 0)
		{
			texy = (int)rc->texPos & (rc->tHeight[0] - 1);
			rc->color = rc->texture[0][rc->tHeight[0] * texy + rc->texX];
			my_mlx_pixel_put(cub, x, i, rc->color);
		}
		else
		{
			texy = (int)rc->texPos & (rc->tHeight[1] - 1);
			rc->color = rc->texture[1][rc->tHeight[1] * texy + rc->texX];
			my_mlx_pixel_put(cub, x, i, rc->color);
		}
	}
	else
		next2(cub, rc, x, i);
}

void	floop(t_cub *cub, t_raycast *rc, int x)
{
	int		i;

	i = rc->drawEnd;
	while (i < cub->extension_height)
	{
		my_mlx_pixel_put(cub, x, i, cub->floor);
		i++;
	}
}

void	texture_coordinate_stepping(t_cub *cub, t_raycast *rc, int x)
{
	int		i;

	i = 0;
	if (rc->side == 0)
	{
		if (rc->stepX < 0)
			rc->step = 1.0 * rc->tHeight[0] / rc->lineHeight;
		else
			rc->step = 1.0 * rc->tHeight[1] / rc->lineHeight;
	}
	else
	{
		if (rc->stepY < 0)
			rc->step = 1.0 * rc->tHeight[2] / rc->lineHeight;
		else
			rc->step = 1.0 * rc->tHeight[3] / rc->lineHeight;
	}
	while (i < rc->drawStart)
		my_mlx_pixel_put(cub, x, i++, cub->ceilling);
	rc->texPos = (rc->drawStart - cub->extension_height
	/ 2 + rc->lineHeight / 2) * rc->step;
	i = rc->drawStart;
	while (i < rc->drawEnd)
		next(cub, rc, x, i++);
	floop(cub, rc, x);
}
