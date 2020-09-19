/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 17:40:43 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/19 15:50:33 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"
#include "get_next_line.h"

void	position2(t_cub *cub, int x, int y)
{
	if (cub->map[y][x] == 'W')
	{
		cub->dirx = -1;
		cub->diry = 0;
		cub->planex = 0;
		cub->planey = -1;
	}
	if (cub->map[y][x] == 'E')
	{
		cub->dirx = 1;
		cub->diry = 0;
		cub->planex = 0;
		cub->planey = 1;
	}
	cub->map[y][x] = '0';
}

void	position(t_cub *cub, int x, int y)
{
	cub->myx = x + 0.5;
	cub->myy = y + 0.5;
	if (cub->map[y][x] == 'N')
	{
		cub->dirx = 0;
		cub->diry = -1;
		cub->planex = 1;
		cub->planey = 0;
	}
	if (cub->map[y][x] == 'S')
	{
		cub->dirx = 0;
		cub->diry = 1;
		cub->planex = -1;
		cub->planey = 0;
	}
	position2(cub, x, y);
}

void	reading(t_cub *cub, char *s)
{
	char	*line;
	int		fd;

	line = ft_strrchr(s, '.');
	if ((ft_strncmp(line, ".cub", ft_strlen(line))))
		error_output(6);
	fd = open(s, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		parsing(line, cub);
		free(line);
	}
	get_next_line(fd, &line);
	parsing(line, cub);
	free(line);
	if (!cub->map1[0])
		error_output(4);
	cub->map = ft_split(cub->map1, '|');
	if (!cub->check || cub->ceilling == -1 || cub->floor == -1)
		error_output(3);
	if (!cub->extension_height || !cub->extension_width)
		error_output(1);
	if (!(check(cub)))
		error_output(4);
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
	if (!(cub->map1 = malloc(sizeof(char) * 1)))
		error_output(5);cub->map1[0] = '\0';
	cub->myx = 0;
	cub->myy = 0;
	cub->movespeed = 0.07;
	cub->rotspeed = 0.03;
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
	cub->ceilling = -1;
	cub->floor = -1;
}

int		main(int argc, char **argv)
{
	t_cub	cub;

	if (argc < 2 || argc > 3)
		return (0);
	struc(&cub);
	reading(&cub, argv[1]);
	chek_scrin(&cub, argv[2]);
	cub.mlx = mlx_init();
	cub.win = mlx_new_window(cub.mlx, cub.extension_width, cub.extension_height, "cub3d");
	movement(&cub);
	cub.img = mlx_new_image(cub.mlx, cub.extension_width, cub.extension_height);
	cub.add = mlx_get_data_addr(cub.img, &cub.pixel, &cub.length, &cub.endian);
	raycasting(&cub);
	if (argv[2] && !(ft_strncmp(argv[2], "--save", 7)))
		scrin_bmp(&cub);
	else if (argv[2])
		return (0);
	cub.check = 0;
	mlx_put_image_to_window(cub.mlx, cub.win, cub.img, 0, 0);
	mlx_destroy_image(cub.mlx, cub.img);
	mlx_loop_hook(cub.mlx, frame, &cub);
	mlx_hook(cub.win, 2, (1L << 0), key_p, &cub);
	mlx_hook(cub.win, 3, (1L << 1), key_u, &cub);
	mlx_hook(cub.win, 17, 0, close_p, &cub);
	mlx_loop(cub.mlx);
}
