/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 16:07:37 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/18 16:40:10 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	coordinate_on_the_texture(t_cub *cub, t_raycast *rc)
{
	double	wallx;

	if (rc->side == 0)
		wallx = cub->myy + rc->perpwalldist * rc->raydiry;
	else
		wallx = cub->myx + rc->perpwalldist * rc->raydirx;
	wallx -= floor((wallx));
	if (rc->side == 0)
	{
		if (rc->stepx < 0)
			rc->texx = (int)(wallx * (double)(cub->twidth[0]));
		else
			rc->texx = (int)(wallx * (double)(cub->twidth[1]));
	}
	else
	{
		if (rc->stepy < 0)
			rc->texx = (int)(wallx * (double)(cub->twidth[2]));
		else
			rc->texx = (int)(wallx * (double)(cub->twidth[3]));
	}
	if (rc->side == 0 && rc->raydirx < 0)
		rc->texx = cub->twidth[0] - rc->texx - 1;
	if (rc->side == 0 && rc->raydirx > 0)
		rc->texx = cub->twidth[1] - rc->texx - 1;
}

void	next2(t_cub *cub, t_raycast *rc, int x, int i)
{
	int	texy;

	if (rc->stepy < 0)
	{
		texy = (int)rc->texpos & (cub->theight[2] - 1);
		rc->color = cub->texture[2][cub->theight[2] * texy + rc->texx];
		my_mlx_pixel_put(cub, x, i, rc->color);
	}
	else
	{
		texy = (int)rc->texpos & (cub->theight[3] - 1);
		rc->color = cub->texture[3][cub->theight[3] * texy + rc->texx];
		my_mlx_pixel_put(cub, x, i, rc->color);
	}
}

void	next(t_cub *cub, t_raycast *rc, int x, int i)
{
	int		texy;

	rc->texpos += rc->step;
	if (rc->side == 0)
	{
		if (rc->stepx < 0)
		{
			texy = (int)rc->texpos & (cub->theight[0] - 1);
			rc->color = cub->texture[0][cub->theight[0] * texy + rc->texx];
			my_mlx_pixel_put(cub, x, i, rc->color);
		}
		else
		{
			texy = (int)rc->texpos & (cub->theight[1] - 1);
			rc->color = cub->texture[1][cub->theight[1] * texy + rc->texx];
			my_mlx_pixel_put(cub, x, i, rc->color);
		}
	}
	else
		next2(cub, rc, x, i);
}

void	floop(t_cub *cub, t_raycast *rc, int x)
{
	int		i;

	i = rc->drawend;
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
		if (rc->stepx < 0)
			rc->step = 1.0 * cub->theight[0] / rc->lineheight;
		else
			rc->step = 1.0 * cub->theight[1] / rc->lineheight;
	}
	else
	{
		if (rc->stepy < 0)
			rc->step = 1.0 * cub->theight[2] / rc->lineheight;
		else
			rc->step = 1.0 * cub->theight[3] / rc->lineheight;
	}
	while (i < rc->drawstart)
		my_mlx_pixel_put(cub, x, i++, cub->ceilling);
	rc->texpos = (rc->drawstart - cub->extension_height
	/ 2 + rc->lineheight / 2) * rc->step;
	i = rc->drawstart;
	while (i < rc->drawend)
		next(cub, rc, x, i++);
	floop(cub, rc, x);
}
