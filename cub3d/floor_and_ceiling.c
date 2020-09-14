/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 14:55:53 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/11 15:11:09 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	rays_and_step(t_cub *cub, t_raycast *rc, int y)
{
	int	p;
	
	rc->rayDirX0 = cub->dirX - cub->planeX;
	rc->rayDirX1 = cub->dirX + cub->planeX;
	rc->rayDirY0 = cub->dirY - cub->planeY;
	rc->rayDirY1 = cub->dirY + cub->planeY;
	p = y - cub->extension_height / 2;
	rc->posZ = 0.5 * cub->extension_height;
	rc->rowDistance = rc->posZ / p;
	rc->floorStepX = rc->rowDistance * (rc->rayDirX1 - rc->rayDirX0) / cub->extension_width;
	rc->floorStepY = rc->rowDistance * (rc->rayDirY1 - rc->rayDirY0) / cub->extension_width;
	rc->floorX = cub->myX + rc->rowDistance * rc->rayDirX0; 
	rc->floorY = cub->myY + rc->rowDistance * rc->rayDirY0;
}

void	texture_rays_and_step(t_cub *cub, t_raycast *rc, int y, int x)
{
	int	cellY;
	int	cellX;
	int	tx;
	int	ty;
	

	cellX = (int)(rc->floorX);
	cellY = (int)(rc->floorY);
	tx = (int)(rc->tWidth[4] * (rc->floorX - cellX)) & (rc->tWidth[4] - 1);
	ty = (int)(rc->tHeight[4] * (rc->floorY - cellY)) & (rc->tHeight[4] - 1);
	rc->floorX += rc->floorStepX;
	rc->floorY += rc->floorStepY;
	rc->color = rc->texture[4][rc->tWidth[4] * ty + tx];
	my_mlx_pixel_put(cub, x, y, rc->color);
	rc->color = rc->texture[5][rc->tWidth[5] * ty + tx];
	my_mlx_pixel_put(cub, x, cub->extension_height - y - 1, rc->color);
}

void	drawing_floor_ceiling(t_cub *cub, t_raycast *rc)
{
	int		y;
	int		x;

	y = 0;
	x = 0;
	while (y < cub->extension_height)
	{
		x = 0;
		rays_and_step(cub, rc, y);
		while (x < cub->extension_width)
		{
			texture_rays_and_step(cub, rc, y, x);
			x++;
		}
		y++;
	}
}

