/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracking_movement.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 16:39:07 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/18 15:24:19 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

int			frame(t_cub *cub)
{
	if (!(cub->w || cub->left || cub->right || cub->a || cub->s || cub->d))
		return (0);
	movement(cub);
	cub->img = mlx_new_image(cub->mlx, cub->extension_width,
	cub->extension_height);
	cub->add = mlx_get_data_addr(cub->img, &cub->pixel,
	&cub->length, &cub->endian);
	raycasting(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	mlx_destroy_image(cub->mlx, cub->img);
	return (0);
}

void		key_w_s(t_cub *cub)
{
	if (cub->w)
	{
		if (cub->map[(int)(cub->myy)][(int)(cub->myx + cub->dirx
			* cub->movespeed)] == '0')
			cub->myx += cub->dirx * cub->movespeed;
		if (cub->map[(int)(cub->myy + cub->diry * cub->movespeed)]
			[(int)(cub->myx)] == '0')
			cub->myy += cub->diry * cub->movespeed;
	}
	if (cub->s)
	{
		if (cub->map[(int)cub->myy][(int)(cub->myx - cub->dirx
			* cub->movespeed)] == '0')
			cub->myx -= cub->dirx * cub->movespeed;
		if (cub->map[(int)(cub->myy - cub->diry * cub->movespeed)]
			[(int)(cub->myx)] == '0')
			cub->myy -= cub->diry * cub->movespeed;
	}
}

void		turn_sideways(t_cub *cub)
{
	double	olddirx;
	double	oldplanex;

	if (cub->left)
	{
		olddirx = cub->dirx;
		cub->dirx = cub->dirx * cos(-cub->rotspeed) - cub->diry
		* sin(-cub->rotspeed);
		cub->diry = olddirx * sin(-cub->rotspeed) + cub->diry
		* cos(-cub->rotspeed);
		oldplanex = cub->planex;
		cub->planex = cub->planex * cos(-cub->rotspeed) - cub->planey
		* sin(-cub->rotspeed);
		cub->planey = oldplanex * sin(-cub->rotspeed) + cub->planey
		* cos(-cub->rotspeed);
	}
}

void		key_a_d(t_cub *cub)
{
	if (cub->d)
	{
		if (cub->map[(int)(cub->myy)][(int)(cub->myx - cub->diry
			* cub->movespeed)] == '0')
			cub->myx -= cub->diry * cub->movespeed;
		if (cub->map[(int)(cub->myy + cub->dirx * cub->movespeed)]
			[(int)(cub->myx)] == '0')
			cub->myy += cub->dirx * cub->movespeed;
	}
	if (cub->a)
	{
		if (cub->map[(int)(cub->myy)][(int)(cub->myx + cub->diry
			* cub->movespeed)] == '0')
			cub->myx += cub->diry * cub->movespeed;
		if (cub->map[(int)(cub->myy - cub->dirx * cub->movespeed)]
			[(int)(cub->myx)] == '0')
			cub->myy -= cub->dirx * cub->movespeed;
	}
}

void		movement(t_cub *cub)
{
	double	olddirx;
	double	oldplanex;

	key_w_s(cub);
	turn_sideways(cub);
	if (cub->right)
	{
		olddirx = cub->dirx;
		cub->dirx = cub->dirx * cos(cub->rotspeed) - cub->diry
		* sin(cub->rotspeed);
		cub->diry = olddirx * sin(cub->rotspeed) + cub->diry
		* cos(cub->rotspeed);
		oldplanex = cub->planex;
		cub->planex = cub->planex * cos(cub->rotspeed) - cub->planey
		* sin(cub->rotspeed);
		cub->planey = oldplanex * sin(cub->rotspeed) + cub->planey
		* cos(cub->rotspeed);
	}
	key_a_d(cub);
}
