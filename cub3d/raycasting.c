/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 18:27:42 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/18 15:00:13 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	rayd(t_cub *cub, t_raycast *rc)
{
	rc->mapX = (int)cub->myX;
	rc->mapY = (int)cub->myY;
	rc->deltaDistX = fabs(1 / rc->rayDirX);
	rc->deltaDistY = fabs(1 / rc->rayDirY);
	if (rc->rayDirX < 0)
	{
		rc->stepX = -1;
		rc->sideDistX = (cub->myX - rc->mapX) * rc->deltaDistX;
	}
	else
	{
		rc->stepX = 1;
		rc->sideDistX = (rc->mapX + 1.0 - cub->myX) * rc->deltaDistX;
	}
	if (rc->rayDirY < 0)
	{
		rc->stepY = -1;
		rc->sideDistY = (cub->myY - rc->mapY) * rc->deltaDistY;
	}
	else
	{
		rc->stepY = 1;
		rc->sideDistY = (rc->mapY + 1.0 - cub->myY) * rc->deltaDistY;
	}
}

void	dda(t_cub *cub, t_raycast *rc)
{
	rc->hit = 0;
	while (rc->hit == 0)
	{
		if (rc->sideDistX < rc->sideDistY)
		{
			rc->sideDistX += rc->deltaDistX;
			rc->mapX += rc->stepX;
			rc->side = 0;
		}
		else
		{
			rc->sideDistY += rc->deltaDistY;
			rc->mapY += rc->stepY;
			rc->side = 1;
		}
		if (cub->map[rc->mapY][rc->mapX] == '1')
			rc->hit = 1;
	}
	if (rc->side == 0)
		rc->perpWallDist = (rc->mapX - cub->myX + (1 - rc->stepX) / 2)
		/ rc->rayDirX;
	else
		rc->perpWallDist = (rc->mapY - cub->myY + (1 - rc->stepY) / 2)
		/ rc->rayDirY;
	rc->lineHeight = (int)(cub->extension_height / rc->perpWallDist);
}

void	texture(t_cub *cub, t_raycast *rc)
{
	void	*tx[6];
	int		b[3];

	if (!(tx[0] = mlx_xpm_file_to_image(cub->mlx, cub->west, &rc->tWidth[0],
	&rc->tHeight[0])))
		error_output(2);
	if(!(tx[1] = mlx_xpm_file_to_image(cub->mlx, cub->east, &rc->tWidth[1],
	&rc->tHeight[1])))
		error_output(2);
	if (!(tx[2] = mlx_xpm_file_to_image(cub->mlx, cub->south, &rc->tWidth[2],
	&rc->tHeight[2])))
		error_output(2);
	if (!(tx[3] = mlx_xpm_file_to_image(cub->mlx, cub->north, &rc->tWidth[3],
	&rc->tHeight[3])))
		error_output(2);
	if (!(tx[4] = mlx_xpm_file_to_image(cub->mlx, cub->sprite, &rc->tWidth[4],
	&rc->tHeight[4])))
		error_output(2);
	rc->texture[0] = (int*)mlx_get_data_addr(tx[0], &b[0], &b[1], &b[2]);
	rc->texture[1] = (int*)mlx_get_data_addr(tx[1], &b[0], &b[1], &b[2]);
	rc->texture[2] = (int*)mlx_get_data_addr(tx[2], &b[0], &b[1], &b[2]);
	rc->texture[3] = (int*)mlx_get_data_addr(tx[3], &b[0], &b[1], &b[2]);
	rc->texture[4] = (int*)mlx_get_data_addr(tx[4], &b[0], &b[1], &b[2]);
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

void	raycasting(t_cub *cub)
{
	int			x;
	double		*zbuffer;
	t_raycast	raycast;

	x = -1;
	if (!(zbuffer = malloc(sizeof(double) * cub->extension_width)))
		error_output(5);
	texture(cub, &raycast);
	while (++x < cub->extension_width)
	{
		raycast.cameraX = 2 * x / (double)cub->extension_width - 1;
		raycast.rayDirX = cub->dirX + cub->planeX * raycast.cameraX;
		raycast.rayDirY = cub->dirY + cub->planeY * raycast.cameraX;
		rayd(cub, &raycast);
		dda(cub, &raycast);
		height_pixel(cub, &raycast);
		coordinate_on_the_texture(cub, &raycast);
		if (raycast.side == 1 && raycast.rayDirY < 0)
			raycast.texX = raycast.tWidth[2] - raycast.texX - 1;
		if (raycast.side == 1 && raycast.rayDirY > 0)
			raycast.texX = raycast.tWidth[3] - raycast.texX - 1;
		texture_coordinate_stepping(cub, &raycast, x);
		zbuffer[x] = raycast.perpWallDist;
	}
	sprites(cub, &raycast, zbuffer);
}
