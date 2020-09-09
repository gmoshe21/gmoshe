/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 16:07:37 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/09 18:44:04 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	coordinate_on_the_texture(t_cub *cub, t_raycast *rc)
{
	double	wallX;
	
	if (rc->side == 0)
		wallX = cub->myY + rc->perpWallDist * rc->rayDirY;
	else
		wallX = cub->myX + rc->perpWallDist * rc->rayDirX;
	wallX -= floor((wallX));
	if (rc->side == 0)
		if (rc->stepX < 0)
			rc->texX = (int)(wallX * (double)(rc->tWidth[0]));
		else
			rc->texX = (int)(wallX * (double)(rc->tWidth[1]));
	else
		if (rc->stepY < 0)
			rc->texX = (int)(wallX * (double)(rc->tWidth[2]));
		else
			rc->texX = (int)(wallX * (double)(rc->tWidth[3]));
	if (rc->side == 0 && rc->rayDirX < 0)
		rc->texX = rc->tWidth[0] - rc->texX - 1;
	if (rc->side == 0 && rc->rayDirX > 0)
		rc->texX = rc->tWidth[1] - rc->texX - 1;
	if (rc->side == 1 && rc->rayDirY < 0)
		rc->texX = rc->tWidth[2] - rc->texX - 1;
	if (rc->side == 1 && rc->rayDirY > 0)
		rc->texX = rc->tWidth[3] - rc->texX - 1;
}

void	next(t_cub *cub, t_raycast *rc, int x, int i)
{
	int		texY;
	
	rc->texPos += rc->step;
	if (rc->side == 0)
		if (rc->stepX < 0)
		{
			texY = (int)rc->texPos & (rc->tHeight[0] - 1);
			rc->color = rc->texture[0][rc->tHeight[0] * texY + rc->texX];
			my_mlx_pixel_put(cub, x, i, rc->color);
		}
		else
		{
			texY = (int)rc->texPos & (rc->tHeight[1] - 1);
			rc->color = rc->texture[1][rc->tHeight[1] * texY + rc->texX];
			my_mlx_pixel_put(cub, x, i, rc->color);
		}
	else
		if (rc->stepY < 0)
		{
			texY = (int)rc->texPos & (rc->tHeight[2] - 1);
			rc->color = rc->texture[2][rc->tHeight[2] * texY + rc->texX];
			my_mlx_pixel_put(cub, x, i, rc->color);
		}
		else
		{
			texY = (int)rc->texPos & (rc->tHeight[3] - 1);
			rc->color = rc->texture[3][rc->tHeight[3] * texY + rc->texX];
			my_mlx_pixel_put(cub, x, i, rc->color);
		}
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
		if (rc->stepX < 0)
			rc->step = 1.0 * rc->tHeight[0] / rc->lineHeight;
		else
			rc->step = 1.0 * rc->tHeight[1] / rc->lineHeight;
	else
		if (rc->stepY < 0)
			rc->step = 1.0 * rc->tHeight[2] / rc->lineHeight;
		else
			rc->step = 1.0 * rc->tHeight[3] / rc->lineHeight;
	while (i < rc->drawStart)
	{
		my_mlx_pixel_put(cub, x, i, cub->ceilling);
		i++;
	}
	rc->texPos = (rc->drawStart - cub->extension_height / 2 +rc->lineHeight / 2) * rc->step;
	i = rc->drawStart;
	while (i < rc->drawEnd)
	{
		next(cub, rc, x, i);
		i++;
	}
	//floop(cub, rc, x);
}