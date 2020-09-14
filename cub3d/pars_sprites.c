/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 14:50:50 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/13 16:45:54 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	pars_sprit(t_cub *cub, int x)
{
	int	i;
	int	j;
	int	k;
	
	i = 0;
	cub->sp = malloc(sizeof(int) * x);
	while (i < x)
	{
		cub->sp[i] = malloc(sizeof(int) * 2);
		i++;
	}
	j = 0;
	i = 0;
	while (cub->map[j])
	{
		k = 0;
		while (cub->map[j][k])
		{
			if (cub->map[j][k] == '2')
			{
				cub->sp[i][0] = j;
				cub->sp[i][1] = k;
				i++;
			}
			k++;
		}
		j++;
	}
}

void		my_map(t_cub *cub)
{
	int		x;
	int		y;

	x = 0;
	y = 0; 
	while (*cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if(cub->map[y][x] == 'N')
				break;
			x++;
		}
		if(cub->map[y][x] == 'N')
		{
			position(cub, x, y);
			break;
		}
		y++;
	}
	x = 0;
	y = 0;
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if(cub->map[y][x] == '2')
				cub->spnum++;
			x++;
		}
		y++;
	}
	pars_sprit(cub, x);
}