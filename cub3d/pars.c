/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 19:35:23 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/09 14:48:36 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"
#include "libft.h"

void pars_other(char *line, t_cub *cub)
{
	while (*line == ' ')
		line++;
	if ((ft_strnstr(line, "R ", 2)))
	{
		line++;
		cub->extension_width = ft_atoi(line);
		while (*line == ' ')
			line++;
		while (*line != ' ')
			line++;
		cub->extension_height = ft_atoi(line);
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

void pars_texture(char *line, t_cub *cub)
{
	char	*texture;
	while (*line == ' ')
		line++;
	line = line + 3;
	texture = ft_strdup(line);
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
	else if ((ft_strnstr(line, "tf ", 2)))
		cub->texfloor = texture;
	else if ((ft_strnstr(line, "tc ", 2)))
		cub->texceilling = texture;
}

void	pars_map(char *line, t_cub *cub)
{
	char	*linemap;
	
	linemap = ft_strjoin(line, "|\0");
	cub->map1 = ft_strjoin(cub->map1, linemap);
	free(linemap);
}

void	parsing(char *line, t_cub *cub)
{
	char	*linemap;
	while (*line == ' ')
		line++;
	if ((ft_strnstr(line, "R ", 2)))
		pars_other(line, cub);
	else if ((ft_strnstr(line, "NO ", 3)))
		pars_texture(line, cub);
	else if ((ft_strnstr(line, "SO ", 3)))
		pars_texture(line, cub);
	else if ((ft_strnstr(line, "WE ", 3)))
		pars_texture(line, cub);
	else if ((ft_strnstr(line, "EA ", 3)))
		pars_texture(line, cub);
	else if ((ft_strnstr(line, "S ", 2)))
		pars_texture(line, cub);
	else if ((ft_strnstr(line, "F ", 2)))
		pars_other(line, cub);
	else if ((ft_strnstr(line, "C ", 2)))
		pars_other(line, cub);
	else if (*line == '1')
	{
		while (*(line - 1) == ' ')
			line--;
		pars_map(line, cub);
	}
}