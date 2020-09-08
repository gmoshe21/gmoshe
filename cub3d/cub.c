/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 17:40:43 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/08 13:19:20 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"
#include "get_next_line.h"
#include "libft.h"

void		position(t_cub *cub, int x, int y)
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

void		my_spr(t_cub *cub)
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
//	while (*cub->map[cub->spY])
//	{
//		cub->spX = 0;
//		while (cub->map[cub->spY][cub->spX])
//		{
//			if(cub->map[cub->spY][cub->spX] == '2')
//				break;
//			cub->spX++;
//		}
//		if(cub->map[cub->spY][cub->spX] == '2')
//			break;
//		cub->spY++;
//	}
}

void		reading(t_cub *cub)
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
	my_spr(cub);
}

void		struc(t_cub *cub, t_raycast *rc)
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
	cub->spX = 0;
	cub->spY = 0;
	rc->moveSpeed = 0.05;
	rc->rotSpeed = 0.03;
}

int	main(void)
{
	t_cub		cub;
	t_raycast	raycast;
	
	struc(&cub, &raycast);
	reading(&cub);
	
	//while (*(cub.map))
	//	printf("%s\n", *(cub.map++));
	//printf("dl = %d,", dl);
	printf("my = %d ", cub.floor);
	printf("%d\n", cub.ceilling);
	//printf("%d\n", sh);
	cub.mlx = mlx_init();
	cub.win = mlx_new_window(cub.mlx, cub.extension_width, cub.extension_height, "cub3d");
	movement(&cub, &raycast);
	cub.img = mlx_new_image(cub.mlx, cub.extension_width, cub.extension_height);
	cub.add = mlx_get_data_addr(cub.img, &cub.pixel, &cub.length, &cub.endian);
	raycasting(&cub, &raycast);
	mlx_put_image_to_window(cub.mlx, cub.win, cub.img, 0, 0);
	mlx_destroy_image(cub.mlx, cub.win);
	mlx_loop_hook(cub.mlx, draw_frame, &cub, &raycast);
	mlx_hook(cub.win, 2, (1L<<0), key_p, &cub);
	mlx_hook(cub.win, 3, (1L<<1), key_u, &cub);
	
	mlx_loop(cub.mlx);
	//while(*cub.map)
	//{
	//	printf("%s\n", *cub.map);
	//	cub.map++;
	//}
	//return (0);
}
