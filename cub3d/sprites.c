/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 16:52:43 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/14 16:19:44 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	sort(int *sprite_order, double *spriteDistance, int numSprites)
{
	int		i;
	int		x;
	double	z;
	int		check;

	i = 0;
	while (check)
	{
		check = 0;
		i = 0;
		while (i < numSprites)
		{
			if (spriteDistance[i] < spriteDistance[i + 1])
			{
				x = sprite_order[i];
				sprite_order[i] = sprite_order[i + 1];
				sprite_order[i + 1] = x;
				z = spriteDistance[i];
				spriteDistance[i] = spriteDistance[i + 1];
				spriteDistance[i + 1] = z;
				check = 1;
			}
			i++;
		}
	}
}

void	sort_sprit(t_cub *cub, t_raycast *rc, int spriteOrder[cub->spnum])
{
	int		i;
	double	spriteDistance[cub->spnum];

	i = 0;
	while (i < cub->spnum)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((cub->myX - cub->sp[i][1]) * (cub->myX - cub->sp[i][1]) + (cub->myY - cub->sp[i][0]) * (cub->myY - cub->sp[i][0]));
		i++;
	}
	sort(spriteOrder, spriteDistance, cub->spnum);
}

void	drawing_sprites(t_cub *cub, t_raycast *rc, double *ZBuffer)
{
	int	x;
	int	y;
	int	texX;
	int	texY;
	int	z;

	x = rc->drawStartX;
	while (x < rc->drawEndX)
	{
		texX = (int)(256 * (x - (-rc->spriteWidth / 2 + rc->spriteScreenX)) * rc->tWidth[6] / rc->spriteWidth) / 256;
		if (rc->transformY > 0 && x > 0 && x < cub->extension_width && rc->transformY < ZBuffer[x])
		{
			y = rc->drawStartY;
			while (y < rc->drawEndY)
			{
				z = (y) * 256 - cub->extension_height * 128 + rc->spriteHeight * 128;
				texY = ((z * rc->tHeight[6]) / rc->spriteHeight) / 256;
				rc->color = rc->texture[6][rc->tHeight[6] * texY + texX];
				if(rc->color != 0x000000)
				my_mlx_pixel_put(cub, x, y, rc->color);
				y++;
			}
		}
		x++;
	}
}

void	sprites(t_cub *cub, t_raycast *rc, double *ZBuffer)
{
	int	spriteOrder[cub->spnum];
	int	i;
	
	i = 0;
	sort_sprit(cub, rc, spriteOrder);
	while(i < cub->spnum)
	{
	rc->spriteX = cub->sp[spriteOrder[i]][1] + 0.5 - cub->myX;
	rc->spriteY = cub->sp[spriteOrder[i]][0] + 0.5 - cub->myY;
	rc->invDet = 1.0 / (cub->planeX * cub->dirY - cub->dirX *cub->planeY);
	rc->transformX = rc->invDet * (rc->spriteX * cub->dirY - cub->dirX * rc->spriteY);
	rc->transformY = rc->invDet * (rc->spriteX * (-cub->planeY) + cub->planeX * rc->spriteY);
	rc->spriteScreenX = (int)((cub->extension_width / 2) * ( 1 + rc->transformX / rc->transformY));
	rc->spriteHeight = abs((int)(cub->extension_height / rc->transformY));
	rc->drawStartY = -rc->spriteHeight / 2 + cub->extension_height / 2;
	if(rc->drawStartY < 0)
		rc->drawStartY = 0;
	rc->drawEndY = rc->spriteHeight / 2 + cub->extension_height / 2;
	if(rc->drawEndY >= cub->extension_height)
		rc->drawEndY = cub->extension_height - 1;
	rc->spriteWidth = abs((int)(cub->extension_height / (rc->transformY)));
	rc->drawStartX = -rc->spriteWidth / 2 + rc->spriteScreenX;
	if(rc->drawStartX < 0)
	rc->drawStartX = 0;
	rc->drawEndX = rc->spriteWidth / 2 + rc->spriteScreenX;
	if(rc->drawEndX >= cub->extension_width)
		rc->drawEndX = cub->extension_width - 1;
	drawing_sprites(cub, rc, ZBuffer);
	i++;
	}
}