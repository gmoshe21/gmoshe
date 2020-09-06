/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 16:07:37 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/05 17:55:34 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	coordinate_on_the_texture(t_cub *cub, t_raycast *rc)
{
	double	wallX;
	
	if (rc->side == 0)
		wallX = cub->myY + rc->perpWallDist * rc->rayDirY;
	else
		wallX = cub->myX + rc->perpWallDist * rc->rayDirX;
	wallX -= floop((wallX));
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

void	next(t_cub *cub, t_raycast *rc, int x)
{
	
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
		my_mlx_pixel_put();
		i++;
	}
	rc->texPos = rc->drawStart - cub->extension_height / 2 +rc->lineHeight / 2) * rc->step;
	next(cub, rc, x);
}