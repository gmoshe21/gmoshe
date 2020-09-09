/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracking_movement.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 16:39:07 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/08 18:39:53 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

int			frame(t_cub *cub)
{
  if (!(cub->w || cub->left || cub->right || cub->a || cub->s || cub->d))
    return (0);
	movement(cub);
	cub->img = mlx_new_image(cub->mlx, cub->extension_width, cub->extension_height);
	cub->add =  mlx_get_data_addr(cub->img, &cub->pixel, &cub->length, &cub->endian);
	raycasting(cub);
  //mlx_do_sync(game->mlx);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	mlx_destroy_image(cub->mlx, cub->img);
	return (0);
}

void	key_w_s(t_cub *cub)
{
	if (cub->w)
	{
		if(cub->map[(int)(cub->myY)][(int)(cub->myX + cub->dirX * cub->moveSpeed)] == '0')
			cub->myX += cub->dirX * cub->moveSpeed;
		if(cub->map[(int)(cub->myY + cub->dirY * cub->moveSpeed)][(int)(cub->myX)] == '0')
			cub->myY += cub->dirY * cub->moveSpeed;
	}
	if (cub->s)
	{
		if (cub->map[(int)cub->myY][(int)(cub->myX - cub->dirX * cub->moveSpeed)] == '0')
			cub->myX -= cub->dirX * cub->moveSpeed;
		if(cub->map[(int)(cub->myY - cub->dirY * cub->moveSpeed)][(int)(cub->myX)] == '0')
			cub->myY -= cub->dirY * cub->moveSpeed;
	}
}

void	turn_sideways(t_cub *cub)
{
	double	olddirX;
	double	oldplaneX;
	if (cub->left)
	{
		olddirX = cub->dirX;
		cub->dirX = cub->dirX * cos(-cub->rotSpeed) - cub->dirY * sin(-cub->rotSpeed);
		cub->dirY = olddirX * sin(-cub->rotSpeed) + cub->dirY * cos(-cub->rotSpeed);
		oldplaneX = cub->planeX;
		cub->planeX = cub->planeX * cos(-cub->rotSpeed) - cub->planeY * sin(-cub->rotSpeed);
		cub->planeY = oldplaneX * sin(-cub->rotSpeed) + cub->planeY * cos(-cub->rotSpeed);
	}
	if (cub->right)
	{
		olddirX = cub->dirX;
		cub->dirX = cub->dirX * cos(cub->rotSpeed) - cub->dirY * sin(cub->rotSpeed);
		cub->dirY = olddirX * sin(cub->rotSpeed) + cub->dirY * cos(cub->rotSpeed);
		oldplaneX = cub->planeX;
		cub->planeX = cub->planeX * cos(cub->rotSpeed) - cub->planeY * sin(cub->rotSpeed);
		cub->planeY = oldplaneX * sin(cub->rotSpeed) + cub->planeY * cos(cub->rotSpeed);
	}
}

void	key_a_d(t_cub *cub)
{
	if (cub->d)
	{
		if(cub->map[(int)(cub->myY)][(int)(cub->myX - cub->dirY * cub->moveSpeed)] == '0')
			cub->myX -= cub->dirY * cub->moveSpeed ;
		if(cub->map[(int)(cub->myY + cub->dirX * cub->moveSpeed)][(int)(cub->myX)] == '0')
			cub->myY += cub->dirX * cub->moveSpeed ;
	}
	if (cub->a)
	{
		if(cub->map[(int)(cub->myY)][(int)(cub->myX + cub->dirY * cub->moveSpeed)] == '0')
			cub->myX += cub->dirY * cub->moveSpeed ;
		if(cub->map[(int)(cub->myY - cub->dirX * cub->moveSpeed)][(int)(cub->myX)] == '0')
			cub->myY -= cub->dirX * cub->moveSpeed ;
	}
}

void	movement(t_cub *cub)
{
	key_w_s(cub);
	turn_sideways(cub);
	key_a_d(cub);
}