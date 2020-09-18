/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 18:27:42 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/18 16:41:27 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	rayd(t_cub *cub, t_raycast *rc)
{
	rc->mapx = (int)cub->myx;
	rc->mapy = (int)cub->myy;
	rc->deltadistx = fabs(1 / rc->raydirx);
	rc->deltadisty = fabs(1 / rc->raydiry);
	if (rc->raydirx < 0)
	{
		rc->stepx = -1;
		rc->sidedistx = (cub->myx - rc->mapx) * rc->deltadistx;
	}
	else
	{
		rc->stepx = 1;
		rc->sidedistx = (rc->mapx + 1.0 - cub->myx) * rc->deltadistx;
	}
	if (rc->raydiry < 0)
	{
		rc->stepy = -1;
		rc->sidedisty = (cub->myy - rc->mapy) * rc->deltadisty;
	}
	else
	{
		rc->stepy = 1;
		rc->sidedisty = (rc->mapy + 1.0 - cub->myy) * rc->deltadisty;
	}
}

void	dda(t_cub *cub, t_raycast *rc)
{
	rc->hit = 0;
	while (rc->hit == 0)
	{
		if (rc->sidedistx < rc->sidedisty)
		{
			rc->sidedistx += rc->deltadistx;
			rc->mapx += rc->stepx;
			rc->side = 0;
		}
		else
		{
			rc->sidedisty += rc->deltadisty;
			rc->mapy += rc->stepy;
			rc->side = 1;
		}
		if (cub->map[rc->mapy][rc->mapx] == '1')
			rc->hit = 1;
	}
	if (rc->side == 0)
		rc->perpwalldist = (rc->mapx - cub->myx + (1 - rc->stepx) / 2)
		/ rc->raydirx;
	else
		rc->perpwalldist = (rc->mapy - cub->myy + (1 - rc->stepy) / 2)
		/ rc->raydiry;
	rc->lineheight = (int)(cub->extension_height / rc->perpwalldist);
}

void	texture(t_cub *cub, t_raycast *rc)
{
	void	*tx[6];
	int		b[3];

	if (!(tx[0] = mlx_xpm_file_to_image(cub->mlx, cub->west, &cub->twidth[0],
	&cub->theight[0])))
		error_output(2);
	if (!(tx[1] = mlx_xpm_file_to_image(cub->mlx, cub->east, &cub->twidth[1],
	&cub->theight[1])))
		error_output(2);
	if (!(tx[2] = mlx_xpm_file_to_image(cub->mlx, cub->south, &cub->twidth[2],
	&cub->theight[2])))
		error_output(2);
	if (!(tx[3] = mlx_xpm_file_to_image(cub->mlx, cub->north, &cub->twidth[3],
	&cub->theight[3])))
		error_output(2);
	if (!(tx[4] = mlx_xpm_file_to_image(cub->mlx, cub->sprite, &cub->twidth[4],
	&cub->theight[4])))
		error_output(2);
	cub->texture[0] = (int*)mlx_get_data_addr(tx[0], &b[0], &b[1], &b[2]);
	cub->texture[1] = (int*)mlx_get_data_addr(tx[1], &b[0], &b[1], &b[2]);
	cub->texture[2] = (int*)mlx_get_data_addr(tx[2], &b[0], &b[1], &b[2]);
	cub->texture[3] = (int*)mlx_get_data_addr(tx[3], &b[0], &b[1], &b[2]);
	cub->texture[4] = (int*)mlx_get_data_addr(tx[4], &b[0], &b[1], &b[2]);
}

void	height_pixel(t_cub *cub, t_raycast *rc)
{
	rc->lineheight = (int)(cub->extension_height / rc->perpwalldist);
	rc->drawstart = -rc->lineheight / 2 + cub->extension_height / 2;
	if (rc->drawstart < 0)
		rc->drawstart = 0;
	rc->drawend = rc->lineheight / 2 + cub->extension_height / 2;
	if (rc->drawend > cub->extension_height)
		rc->drawend = cub->extension_height - 1;
}

void	raycasting(t_cub *cub)
{
	int			x;
	double		*zbuffer;
	t_raycast	raycast;

	x = -1;
	if (!(zbuffer = malloc(sizeof(double) * cub->extension_width)))
		error_output(5);
	if (cub->check)
		texture(cub, &raycast);
	while (++x < cub->extension_width)
	{
		raycast.camerax = 2 * x / (double)cub->extension_width - 1;
		raycast.raydirx = cub->dirx + cub->planex * raycast.camerax;
		raycast.raydiry = cub->diry + cub->planey * raycast.camerax;
		rayd(cub, &raycast);
		dda(cub, &raycast);
		height_pixel(cub, &raycast);
		coordinate_on_the_texture(cub, &raycast);
		if (raycast.side == 1 && raycast.raydiry < 0)
			raycast.texx = cub->twidth[2] - raycast.texx - 1;
		if (raycast.side == 1 && raycast.raydiry > 0)
			raycast.texx = cub->twidth[3] - raycast.texx - 1;
		texture_coordinate_stepping(cub, &raycast, x);
		zbuffer[x] = raycast.perpwalldist;
	}
	sprites(cub, &raycast, zbuffer);
}
