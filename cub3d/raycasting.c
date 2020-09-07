/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 18:27:42 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/07 18:22:11 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	rayd(t_cub *cub, t_raycast *rc)
{
	if (rc->rayDirX < 0)
	{
		rc->stepX = -1;
		rc->sideDistX = (cub->myX - rc->mapX) * rc->deltaDistX;
	}
	else
	{
		rc->stepX = 1;
		rc->sideDistX = (cub->myX + 1.0 - rc->mapX) * rc->deltaDistX;
	}
	if (rc->rayDirY < 0)
	{
		rc->stepY = -1;
		rc->sideDistY = (cub->myY - rc->mapY) * rc->deltaDistY;
	}
	else
	{
		rc->stepY = 1;
		rc->sideDistY = (cub->myY + 1.0 - rc->mapY) * rc->deltaDistY;
	}
}

void	dda(t_cub *cub, t_raycast *rc)
{
	while (rc->hit == 0)
	{
		if (rc->deltaDistX < rc->deltaDistY)
		{
			rc->deltaDistX += rc->deltaDistX;
			rc->mapX += rc->stepX;
			rc->side = 0;
		}
		else
		{
			rc->deltaDistY += rc->deltaDistY;
			rc->mapY += rc->stepY;
			rc->side = 1;
		}
		if (cub->map[rc->mapY][rc->mapX] == '1')
			rc->hit = 1;
	}
	if (rc->side == 0)
		rc->perpWallDist = (rc->mapX - cub->myX + (1 - rc->stepX) / 2) / rc->rayDirX;
	else
		rc->perpWallDist = (rc->mapY - cub->myY + (1 - rc->stepY) / 2) / rc->rayDirY;
	rc->lineHeight = (int)(cub->extension_height / rc->perpWallDist);
}

void	texture(t_cub *cub, t_raycast *rc)
{
	void	*tx[4];
	int		b;
	int		s;
	int		e;
	
	tx[0] = mlx_xpm_file_to_image(cub->mlx, cub->west, &rc->tWidth[0], &rc->tHeight[0]);
	tx[1] = mlx_xpm_file_to_image(cub->mlx, cub->east, &rc->tWidth[1], &rc->tHeight[1]);
	tx[2] = mlx_xpm_file_to_image(cub->mlx, cub->south, &rc->tWidth[2], &rc->tHeight[2]);
	tx[3] = mlx_xpm_file_to_image(cub->mlx, cub->north, &rc->tWidth[3], &rc->tHeight[3]);
	rc->texture[0] = (int*)mlx_get_data_addr(tx[0], &b, &s, &e);
	rc->texture[1] = (int*)mlx_get_data_addr(tx[1], &b, &s, &e);
	rc->texture[2] = (int*)mlx_get_data_addr(tx[2], &b, &s, &e);
	rc->texture[3] = (int*)mlx_get_data_addr(tx[3], &b, &s, &e);
}

void	height_pixel(t_cub *cub, t_raycast *rc)
{
	rc->lineHeight = (int)(cub->extension_height / rc->perpWallDist);
	rc->drawStart = -rc->lineHeight / 2 + cub->extension_height / 2;
	if (rc->drawStart < 0)
		rc->drawStart = 0;
	rc->drawEnd = rc->lineHeight / 2 + cub->extension_height / 2;
	if (rc->drawEnd > cub->extension_height)
		rc->drawEnd = cub->extension_height - 1;
}

void	raycasting(t_cub *cub, t_raycast *rc)
{
	int	x;

	x = 0;
	texture(cub, rc);
	while (x < cub->extension_width)
	{
		rc->cameraX = 2 * x / (double)cub->extension_width - 1;
		rc->rayDirX = cub->dirX + cub->planeX * rc->cameraX;
		rc->rayDirY = cub->dirY + cub->planeY * rc->cameraX;
		rc->mapX = (int)cub->myX;
		rc->mapY = (int)cub->myY;
		rc->deltaDistX = fabs(1 / rc->rayDirX);
		rc->deltaDistX = fabs(1 / rc->rayDirY);
		rayd(cub, rc);
		dda(cub, rc);
		height_pixel(cub, rc);
		coordinate_on_the_texture(cub, rc);
		texture_coordinate_stepping(cub, rc, x);
		x++;
	}
}
