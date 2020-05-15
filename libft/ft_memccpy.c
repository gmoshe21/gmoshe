/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.tr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 14:58:41 by gmoshe            #+#    #+#             */
/*   Updated: 2020/05/15 14:58:44 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *destination, const void *source, int c, size_t n)
{
	size_t	i;

	i = 0;
	if (!destination && !source)
		return (NULL);
	while (n != 0)
	{
		((unsigned char*)destination)[i] = ((unsigned char*)source)[i];
		if (((unsigned char*)source)[i] == (unsigned char)c)
		{
			return ((unsigned char*)destination + i + 1);
		}
		i++;
		n--;
	}
	return (NULL);
}
