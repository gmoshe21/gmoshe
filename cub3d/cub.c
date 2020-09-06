/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 17:40:43 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/05 18:05:51 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"
#include "get_next_line.h"
#include "libft.h"

void		my_spr(t_cub *cub)
{
	while (*cub->map[cub->myY])
	{
		cub->myX = 0;
		while (cub->map[cub->myY][cub->myX])
		{
			if(cub->map[cub->myY][cub->myX] == 'N')
				break;
			cub->myX++;
		}
		if(cub->map[cub->myY][cub->myX] == 'N')
			break;
		cub->myY++;
	}
	while (*cub->map[cub->spY])
	{
		cub->spX = 0;
		while (cub->map[cub->spY][cub->spX])
		{
			if(cub->map[cub->spY][cub->spX] == '2')
				break;
			cub->spX++;
		}
		if(cub->map[cub->spY][cub->spX] == '2')
			break;
		cub->spY++;
	}
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

void		struc(t_cub *cub)
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
}

int	main(void)
{
	t_cub		cub;
	t_raycast	raycast;
	void		*mlx;
	void		*win;
	int			dl = 0;
	int			sh = 0;
	
	mlx = NULL;
	win = NULL;
	struc(&cub);
	reading(&cub);
	dl = 2 | 5;
	//while (*(cub.map))
	//	printf("%s\n", *(cub.map++));
	printf("dl = %d,", dl);
	printf("sp = %d,", cub.spX);
	printf("%d\n", cub.spY);
	printf("my = %d,", cub.myX);
	printf("%d\n", cub.myY);
	printf("%d\n", sh);
	//mlx = mlx_init();
	//win = mlx_new_window(mlx, cub.extension_width, cub.extension_height, "cub3d");
	//mlx_loop(mlx);
	while(*cub.map)
	{
		printf("%s\n", *cub.map);
		cub.map++;
	}
	return (0);
}
