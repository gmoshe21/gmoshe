/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 17:18:55 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/18 13:03:21 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"
#include "libft.h"

void	error_output(int i)
{
	if (i == 1)
		write(1, "invalid screen resolution", 25);
	if (i == 2)
		write(1, "not valid texture", 17);
	if (i == 3)
		write(1, "not a valid floor or ceiling color", 34);
	if (i == 4)
		write(1, "not valid map", 13);
	if (i == 5)
		write(1, "memory allocation error", 23);
	exit(0);
}

void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*put;

	put = cub->add + (y * cub->length + x * (cub->pixel / 8));
	*(unsigned int*)put = color;
}

void	ft_color(t_cub *cub, char *line)
{
	char	**str;

	if ((ft_strnstr(line, "F ", 2)))
	{
		line = line + 2;
		str = ft_split(line, ',');
		valid_floor_ceilling(cub, str);
		cub->floor = 0;
		cub->floor = ft_atoi(str[0]) << 16;
		cub->floor = cub->floor | (ft_atoi(str[1]) << 8);
		cub->floor = cub->floor | ft_atoi(str[2]);
	}
	else if ((ft_strnstr(line, "C ", 2)))
	{
		line = line + 2;
		str = ft_split(line, ',');
		valid_floor_ceilling(cub, str);
		cub->ceilling = 0;
		cub->ceilling = ft_atoi(str[0]) << 16;
		cub->ceilling = cub->ceilling | (ft_atoi(str[1]) << 8);
		cub->ceilling = cub->ceilling | ft_atoi(str[2]);
	}
	valid_floor_ceilling(cub, str);
}

int		key_p(int key, t_cub *cub)
{
	if (key == 53)
		exit(0);
	if (key == key_W)
		cub->w = 1;
	if (key == key_S)
		cub->s = 1;
	if (key == key_left)
		cub->left = 1;
	if (key == key_right)
		cub->right = 1;
	if (key == key_A)
		cub->a = 1;
	if (key == key_D)
		cub->d = 1;
	return (0);
}

int		key_u(int key, t_cub *cub)
{
	if (key == key_W)
		cub->w = 0;
	if (key == key_S)
		cub->s = 0;
	if (key == key_left)
		cub->left = 0;
	if (key == key_right)
		cub->right = 0;
	if (key == key_A)
		cub->a = 0;
	if (key == key_D)
		cub->d = 0;
	return (0);
}
