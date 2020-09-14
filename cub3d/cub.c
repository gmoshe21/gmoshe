/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 17:40:43 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/14 18:57:24 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"
#include "get_next_line.h"
#include "libft.h"

void	position2(t_cub *cub, int x, int y)
{
	if (cub->map[y][x] == 'W')
	{
		cub->dirX = -1;
		cub->dirY = 0;
		cub->planeX = 0;
		cub->planeY = -1;
	}
	if (cub->map[y][x] == 'E')
	{
		cub->dirX = 1;
		cub->dirY = 0;
		cub->planeX = 0;
		cub->planeY = 1;
	}
	cub->map[y][x] = '0';
}

void	position(t_cub *cub, int x, int y)
{
	cub->myX = x + 0.5;
	cub->myY = y + 0.5;
	if (cub->map[y][x] == 'N')
	{
		cub->dirX = 0;
		cub->dirY = -1;
		cub->planeX = 1;
		cub->planeY = 0;
	}
	if (cub->map[y][x] == 'S')
	{
		cub->dirX = 0;
		cub->dirY = 1;
		cub->planeX = -1;
		cub->planeY = 0;
	}
	position2(cub, x, y);
}

void	reading(t_cub *cub)
{
	char	*line;
	int		fd;

	fd = open("cub.txt", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		parsing(line, cub);
		free(line);
	}
	get_next_line(fd, &line);
	parsing(line, cub);
	free(line);
	cub->map = ft_split(cub->map1, '|');
	if(!(check(cub)))
		cub->check = 0;
	my_map(cub);
}

void	struc(t_cub *cub)
{
	cub->north = NULL;
	cub->south = NULL;
	cub->west = NULL;
	cub->east = NULL;
	cub->sprite = NULL;
	cub->extension_height = 0;
	cub->extension_width = 0;
	cub->map1 = malloc(sizeof(char) * 1);
	cub->map1[0] = '\0';
	cub->myX = 0;
	cub->myY = 0;
	cub->moveSpeed = 0.05;
	cub->rotSpeed = 0.03;
	cub->w = 0;
	cub->s = 0;
	cub->a = 0;
	cub->d = 0;
	cub->left = 0;
	cub->right = 0;
	cub->mlx = NULL;
	cub->win = NULL;
	cub->spnum = 0;
	cub->check = 1;
}

int		main(void)
{
	t_cub	cub;

	struc(&cub);
	reading(&cub);
	if (!cub.check)
	{
		write(1, "error", 5);
		return (0);
	}
	cub.mlx = mlx_init();
	cub.win = mlx_new_window(cub.mlx, cub.extension_width, cub.extension_height, "cub3d");
	movement(&cub);
	cub.img = mlx_new_image(cub.mlx, cub.extension_width, cub.extension_height);
	cub.add = mlx_get_data_addr(cub.img, &cub.pixel, &cub.length, &cub.endian);
	raycasting(&cub);
	mlx_put_image_to_window(cub.mlx, cub.win, cub.img, 0, 0);
	mlx_destroy_image(cub.mlx, cub.img);
	mlx_loop_hook(cub.mlx, frame, &cub);
	mlx_hook(cub.win, 2, (1L << 0), key_p, &cub);
	mlx_hook(cub.win, 3, (1L << 1), key_u, &cub);
	mlx_loop(cub.mlx);
}
