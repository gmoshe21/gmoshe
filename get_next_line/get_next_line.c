/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.tr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 18:00:20 by gmoshe            #+#    #+#             */
/*   Updated: 2020/06/27 12:32:06 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*write_line(char *ost)
{
	int		len;
	char	*line;

	len = 0;
	if (!ost)
		return (0);
	while (ost[len] != '\0' && ost[len] != '\n')
		len++;
	if (!(line = malloc(sizeof(char) * (len + 1))))
		return (0);
	len = 0;
	while (ost[len] != '\0' && ost[len] != '\n')
	{
		line[len] = ost[len];
		len++;
	}
	line[len] = '\0';
	return (line);
}

char	*write_ost(char *ost)
{
	char	*new;
	int		del;
	int		i;

	del = 0;
	i = 0;
	if (!ost)
		return (0);
	while (ost[del] != '\0' && ost[del] != '\n')
		del++;
	if (!ost[del])
	{
		free(ost);
		return (0);
	}
	if (!(new = malloc(sizeof(char) * ((ft_strlen(ost) - del) + 1))))
		return (0);
	del++;
	while (ost[del])
		new[i++] = ost[del++];
	new[i] = '\0';
	free(ost);
	return (new);
}

int		get_next_line(int fd, char **line)
{
	char			*buf;
	static char		*ost;
	int				read_file;

	read_file = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!ost_n(ost) && read_file != 0)
	{
		if ((read_file = read(fd, buf, BUFFER_SIZE)) == -1)
		{
			free(buf);
			return (-1);
		}
		buf[read_file] = '\0';
		CHECK((ost = ft_strjoin(ost, buf)));
	}
	free(buf);
	CHECK((*line = write_line(ost)));
	ost = write_ost(ost);
	if (read_file == 0)
		return (0);
	return (1);
}
