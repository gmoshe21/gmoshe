/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.tr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 02:50:02 by gmoshe            #+#    #+#             */
/*   Updated: 2020/05/16 02:50:05 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	x;
	char	*s3;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = ft_strlen(s1);
	x = ft_strlen(s2);
	if (!(s3 = (char*)ft_calloc(i + x + 1, sizeof(char))))
		return (0);
	i = 0;
	x = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[x])
	{
		s3[i] = s2[x];
		x++;
		i++;
	}
	s3[i] = '\0';
	return (s3);
}
