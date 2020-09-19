/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 16:52:43 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/19 15:38:52 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	sort(int *sprite_order, double *spritedistance, int numsprites)
{
	int		i;
	int		x;
	double	z;
	int		check;

	check = 1;
	while (check)
	{
		check = 0;
		i = 0;
		while (i < numsprites)
		{
			if (spritedistance[i] < spritedistance[i + 1])
			{
				x = sprite_order[i];
				sprite_order[i] = sprite_order[i + 1];
				sprite_order[i + 1] = x;
				z = spritedistance[i];
				spritedistance[i] = spritedistance[i + 1];
				spritedistance[i + 1] = z;
				check = 1;
			}
			i++;
		}
	}
}

void	sort_sprit(t_cub *cub, t_raycast *rc, int spriteorder[cub->spnum])
{
	int		i;
	double	spritedistance[cub->spnum];

	i = 0;
	while (i < cub->spnum)
	{
		spriteorder[i] = i;
		spritedistance[i] = ((cub->myx - cub->sp[i][1]) * (cub->myx
		- cub->sp[i][1]) + (cub->myy - cub->sp[i][0])
		* (cub->myy - cub->sp[i][0]));
		i++;
	}
	sort(spriteorder, spritedistance, cub->spnum);
}

void	drawing_sprites(t_cub *cub, t_raycast *rc, double *zbuffer, int z)
{
	int	x;
	int	y;
	int	texx;
	int	texy;

	x = rc->drawstarts - 1;
	while (++x < rc->drawendx)
	{
		texx = (int)(256 * (x - (-rc->spritewidth / 2 + rc->spritescreenx))
		* cub->twidth[4] / rc->spritewidth) / 256;
		if (rc->transformy > 0 && x > 0 && x < cub->extension_width
			&& rc->transformy < zbuffer[x])
		{
			y = rc->drawstarty - 1;
			while (++y < rc->drawendy)
			{
				z = (y) * 256 - cub->extension_height * 128
				+ rc->spriteheight * 128;
				texy = ((z * cub->theight[4]) / rc->spriteheight) / 256;
				rc->color = cub->texture[4][cub->theight[4] * texy + texx];
				if (rc->color != 0x000000)
					my_mlx_pixel_put(cub, x, y, rc->color);
			}
		}
	}
}

void	sprites_next(t_cub *cub, t_raycast *rc, double *zbuffer)
{
	int	z;

	if (rc->drawstarty < 0)
		rc->drawstarty = 0;
	rc->drawendy = rc->spriteheight / 2 + cub->extension_height / 2;
	if (rc->drawendy >= cub->extension_height)
		rc->drawendy = cub->extension_height - 1;
	rc->spritewidth = abs((int)(cub->extension_height / (rc->transformy)));
	rc->drawstarts = -rc->spritewidth / 2 + rc->spritescreenx;
	if (rc->drawstarts < 0)
		rc->drawstarts = 0;
	rc->drawendx = rc->spritewidth / 2 + rc->spritescreenx;
	if (rc->drawendx >= cub->extension_width)
		rc->drawendx = cub->extension_width - 1;
	drawing_sprites(cub, rc, zbuffer, z);
}

void	sprites(t_cub *cub, t_raycast *rc, double *zbuffer)
{
	int	spriteorder[cub->spnum];
	int	i;

	i = 0;
	sort_sprit(cub, rc, spriteorder);
	while (i < cub->spnum)
	{
		rc->spritex = cub->sp[spriteorder[i]][1] + 0.5 - cub->myx;
		rc->spritey = cub->sp[spriteorder[i]][0] + 0.5 - cub->myy;
		rc->invdet = 1.0 / (cub->planex * cub->diry - cub->dirx * cub->planey);
		rc->transformx = rc->invdet * (rc->spritex * cub->diry
		- cub->dirx * rc->spritey);
		rc->transformy = rc->invdet * (rc->spritex * (-cub->planey)
		+ cub->planex * rc->spritey);
		rc->spritescreenx = (int)((cub->extension_width / 2)
		* (1 + rc->transformx / rc->transformy));
		rc->spriteheight = abs((int)(cub->extension_height / rc->transformy));
		rc->drawstarty = -rc->spriteheight / 2 + cub->extension_height / 2;
		sprites_next(cub, rc, zbuffer);
		i++;
	}
	free(zbuffer);
}
