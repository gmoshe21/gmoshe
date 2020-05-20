/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.tr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 03:04:07 by gmoshe            #+#    #+#             */
/*   Updated: 2020/05/16 03:04:11 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *str, int ch)
{
	char	j;
	int		i;

	j = 0;
	i = 0;
	while (ch != 0)
	{
		j++;
		ch--;
	}
	while (str[i])
	{
		if (str[i] == j)
			return ((char*)str + i);
		i++;
	}
	if (str[i] == j)
		return ((char*)str + i);
	return (NULL);
}
