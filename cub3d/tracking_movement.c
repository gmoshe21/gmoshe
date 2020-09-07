/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracking_movement.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 16:39:07 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/07 17:26:51 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	key_w_s(t_cub *cub, t_raycast *rc)
{
	if (cub->w)
	{
		if(cub->map[(int)(cub->myY)][(int)(cub->myX + cub->dirX * rc->moveSpeed)] == '0')
			cub->myX += cub->dirX * rc->moveSpeed;
		if(cub->map[(int)(cub->myY + cub->dirY * rc->moveSpeed)][(int)(cub->myX)] == '0')
			cub->myY += cub->dirY * rc->moveSpeed;
	}
	if (cub->s)
	{
		if (cub->map[(int)cub->myY][(int)(cub->myX - cub->dirX +rc->moveSpeed)] == '0')
			cub->myX -= cub->dirX + rc->moveSpeed;
		if(cub->map[(int)(cub->myY - cub->dirY * rc->moveSpeed)][(int)(cub->myX)] == '0')
			cub->myY -= cub->dirY * rc->moveSpeed;
	}
}

void	turn_sideways(t_cub *cub, t_raycast *rc)
{
	double	olddirX;
	double	oldplaneX;
	if (cub->left)
	{
		olddirX = cub->dirX;
		cub->dirX = cub->dirX * cos(-rc->rotSpeed) - cub->dirY * sin(-rc->rotSpeed);
		cub->dirY = olddirX * sin(-rc->rotSpeed) * cub->dirY * cos(-rc->rotSpeed);
		oldplaneX = cub->planeX;
		cub->planeX = cub->planeX * cos(-rc->rotSpeed) - cub->planeY * sin(-rc->rotSpeed);
		cub->planeY = oldplaneX * sin(-rc->rotSpeed) + cub->planeY * cos(-rc->rotSpeed);
	}
	if (cub->right)
	{
		olddirX = cub->dirX;
		cub->dirX = cub->dirX * cos(rc->rotSpeed) - cub->dirY * sin(rc->rotSpeed);
		cub->dirY = olddirX * sin(rc->rotSpeed) * cub->dirY * cos(rc->rotSpeed);
		oldplaneX = cub->planeX;
		cub->planeX = cub->planeX * cos(rc->rotSpeed) - cub->planeY * sin(rc->rotSpeed);
		cub->planeY = oldplaneX * sin(rc->rotSpeed) + cub->planeY * cos(rc->rotSpeed);
	}
}

void	key_a_d(t_cub *cub, t_raycast *rc)
{
	if (cub->d)
	{
		if(cub->map[(int)(cub->myY)][(int)(cub->myX - cub->dirY * rc->moveSpeed)] == '0')
			cub->myX -= cub->dirY * rc->moveSpeed * 0.5;
		if(cub->map[(int)(cub->myY + cub->dirX * rc->moveSpeed)][(int)(cub->myX)] == '0')
			cub->myY += cub->dirX * rc->moveSpeed * 0.5;
	}
	if (cub->a)
	{
		if(cub->map[(int)(cub->myY)][(int)(cub->myX + cub->dirY * rc->moveSpeed)] == '0')
			cub->myX += cub->dirY * rc->moveSpeed * 0.5;
		if(cub->map[(int)(cub->myY - cub->dirX * rc->moveSpeed)][(int)(cub->myX)] == '0')
			cub->myY -= cub->dirX * rc->moveSpeed * 0.5;
	}
}

void	movementrayd(t_cub *cub, t_raycast *rc)
{
	key_w_s(cub, rc);
	turn_sideways(cub, rc);
	key_a_d(cub, rc);
}