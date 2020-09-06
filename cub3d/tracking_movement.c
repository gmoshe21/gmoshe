/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracking_movement.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 16:39:07 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/06 18:30:11 by gmoshe           ###   ########.fr       */
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
		cub->dirX = cub->dirX * cos(-rotSpeed) - cub->dirY * sin(-rotSpeed);
		cub->dirY = olddirX * sin(-rotSpeed) * cub->dirY * cos(-rotSpeed);
		oldplaneX = cub->planeX;
		cub->planeX = cub->planeX * cos(-rotSpeed) - cub->planeY * sin(-rotSpeed);
		cub->planeY = oldplaneX * sin(-rotSpeed) + cub->planeY * cos(-rotSpeed);
	}
	if (cub->right)
	{
		olddirX = cub->dirX;
		cub->dirX = cub->dirX * cos(rotSpeed) - cub->dirY * sin(rotSpeed);
		cub->dirY = olddirX * sin(rotSpeed) * cub->dirY * cos(rotSpeed);
		oldplaneX = cub->planeX;
		cub->planeX = cub->planeX * cos(rotSpeed) - cub->planeY * sin(rotSpeed);
		cub->planeY = oldplaneX * sin(rotSpeed) + cub->planeY * cos(rotSpeed);
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