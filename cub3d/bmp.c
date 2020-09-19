/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 18:10:13 by gmoshe            #+#    #+#             */
/*   Updated: 2020/09/19 13:54:01 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

int i(int x)
{
	int j;

	j = x;
	while (j % 64)
	{
		j = j - 1;
	}
	return(j);
}

void	chek_scrin(t_cub *cub, char *argv)
{
	if (argv && !(ft_strncmp(argv, "--save", 7)))
	{
		cub->extension_height = i(cub->extension_height);
		cub->extension_width = i(cub->extension_width);
	}
}

void	scrin_bmp(t_cub *cub)
{
	char			*bmp;
	int32_t			num;
	const uint32_t	size = i(cub->extension_height) * cub->extension_width * (cub->pixel >> 3) + 54;

	if (!(bmp = (char*)malloc(size)))
	error_output(5);
	ft_bzero(bmp, size);
	ft_memcpy(&bmp[0], "BM", 2);
	ft_memcpy(&bmp[2], &size, 4);
	num = 54;
	ft_memcpy(&bmp[10], &num, 4);
	num = 40;
	ft_memcpy(&bmp[14], &num, 4);
	num = cub->extension_width;
	ft_memcpy(&bmp[18], &num, 4);
	num = -i(cub->extension_height);
	ft_memcpy(&bmp[22], &num, 4);
	num = 1;
	ft_memcpy(&bmp[26], &num, 2);
	ft_memcpy(&bmp[28], &cub->pixel, 2);
	ft_memcpy(&bmp[54], cub->add, (size - 54));
	num = open("scr.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	(write(num, bmp, size));
	free(bmp);
	close(num);
}
