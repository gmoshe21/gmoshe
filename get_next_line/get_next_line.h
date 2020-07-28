/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.tr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 18:00:49 by gmoshe            #+#    #+#             */
/*   Updated: 2020/06/27 12:22:54 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

int					get_next_line(int fd, char **line);
int					ost_n(char *ost);
size_t				ft_strlen(const char *s);
char				*ft_strjoin(const char *s1, const char *s2);

# define CHECK(x) if(!x) return (-1)
#endif
