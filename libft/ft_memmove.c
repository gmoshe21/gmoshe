/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.tr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 15:08:28 by gmoshe            #+#    #+#             */
/*   Updated: 2020/05/15 15:09:54 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memm(void *dest, const void *source, size_t n)
{
	dest = dest + n - 1;
	source = source + n - 1;
	while (n > 0)
	{
		*(unsigned char*)dest-- = *(unsigned char*)source--;
		n--;
	}
	return ((char*)dest + 1);
}

void			*ft_memmove(void *dest, const void *source, size_t n)
{
	size_t		j;

	j = 0;
	if (!dest && !source)
		return (0);
	if (n == 0)
		return (dest);
	if (dest < source)
	{
		while (n != 0)
		{
			((char*)dest)[j] = ((char*)source)[j];
			j++;
			n--;
		}
	}
	else
		return (ft_memm(dest, source, n));
	return ((char*)dest);
}
