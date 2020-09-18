/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 18:43:20 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/18 15:57:54 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	valid_floor_ceilling(t_cub *cub, char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_atoi(str[i]) > 255 || ft_atoi(str[i]) < 0)
			error_output(3);
		i++;
	}
	if (i != 3)
		error_output(3);
}

int		valid_map(t_cub *cub)
{
	int		x;
	int		y;
	char	z;
	int		poz;

	y = -1;
	poz = 0;
	while (cub->map[++y])
	{
		x = -1;
		while (cub->map[y][++x])
		{
			z = cub->map[y][x];
			if (z != ' ' && z != '1' && z != '0' && z != '2' && z != 'N'
				&& z != 'W' && z != 'E' && z != 'S')
				return (0);
			if (z == 'W' || z == 'S' || z == 'E' || z == 'N')
				poz++;
		}
	}
	if (poz != 1)
		return (0);
	return (1);
}

int		check(t_cub *cub)
{
	int		x;
	int		y;

	y = 0;
	while (cub->map[y + 1])
	{
		x = -1;
		while (cub->map[y][++x])
		{
			if (cub->map[0][x] != ' ' && cub->map[0][x] != '1')
				return (0);
			if ((cub->map[y][x] == '0' || cub->map[y][x] == '2')
				&& (cub->map[y][x + 1] == ' ' || cub->map[y][x - 1] == ' '
				|| cub->map[y + 1][x] == ' ' || cub->map[y - 1][x] == ' '))
				return (0);
		}
		y++;
	}
	x = -1;
	while (cub->map[y][++x])
		if (cub->map[y][x] != ' ' && cub->map[y][x] != '1')
			return (0);
	if (!(valid_map(cub)))
		return (0);
	return (1);
}
