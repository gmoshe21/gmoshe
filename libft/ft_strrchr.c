/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.tr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 15:10:22 by gmoshe            #+#    #+#             */
/*   Updated: 2020/05/15 15:10:25 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *str, int ch)
{
	int		i;
	char	j;

	j = (char)ch;
	i = ft_strlen(str);
	while (i != 0)
	{
		if (str[i] == j)
		{
			while (i != 0)
			{
				str++;
				i--;
			}
			return ((char*)str);
		}
		i--;
	}
	if (str[0] == j)
		return ((char*)str);
	return (NULL);
}
