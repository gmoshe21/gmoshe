/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 19:35:23 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/18 13:19:33 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"
#include "libft.h"

int		close_p(int game, t_cub *cub)
{
	game = 0;
	exit(0);
}

void	pars_other(char *line, t_cub *cub)
{
	if ((ft_strnstr(line, "R ", 2)))
	{
		line++;
		cub->extension_width = ft_atoi(line);
		if (cub->extension_width > 1920 || cub->extension_width < 0)
			cub->extension_width = 1920;
		while (*line == ' ')
			line++;
		while (*line != ' ')
			line++;
		cub->extension_height = ft_atoi(line);
		if (cub->extension_height > 1080 || cub->extension_height < 0)
			cub->extension_height = 1080;
	}
	if ((ft_strnstr(line, "F ", 2)))
	{
		ft_color(cub, line);
	}
	if ((ft_strnstr(line, "C ", 2)))
	{
		ft_color(cub, line);
	}
}

void	pars_texture(char *line, t_cub *cub)
{
	char	*texture;

	while (*line == ' ')
		line++;
	line = line + 3;
	if (!(texture = ft_strdup(line)))
		error_output(5);
	line = line - 3;
	if ((ft_strnstr(line, "NO ", 3)))
		cub->north = texture;
	else if ((ft_strnstr(line, "SO ", 3)))
		cub->south = texture;
	else if ((ft_strnstr(line, "WE ", 3)))
		cub->west = texture;
	else if ((ft_strnstr(line, "EA ", 3)))
		cub->east = texture;
	else if ((ft_strnstr(line, "S ", 2)))
		cub->sprite = texture;
}

void	pars_map(char *line, t_cub *cub)
{
	char	*linemap;

	linemap = ft_strjoin(line, "|\0");
	if (!(cub->map1 = ft_strjoin(cub->map1, linemap)))
		error_output(5);
	free(linemap);
}

void	parsing(char *line, t_cub *cub)
{
	char	*linemap;

	while (*line == ' ')
		line++;
	if ((ft_strnstr(line, "R ", 2)))
		pars_other(line, cub);
	if ((ft_strnstr(line, "NO ", 3)))
		pars_texture(line, cub);
	if ((ft_strnstr(line, "SO ", 3)))
		pars_texture(line, cub);
	if ((ft_strnstr(line, "WE ", 3)))
		pars_texture(line, cub);
	if ((ft_strnstr(line, "EA ", 3)))
		pars_texture(line, cub);
	if ((ft_strnstr(line, "S ", 2)))
		pars_texture(line, cub);
	if ((ft_strnstr(line, "F ", 2)) || (ft_strnstr(line, "C ", 2)))
		pars_other(line, cub);
	if (*line == '1')
	{
		while (*(line - 1) == ' ')
			line--;
		pars_map(line, cub);
	}
}
