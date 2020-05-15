/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.tr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 14:57:20 by gmoshe            #+#    #+#             */
/*   Updated: 2020/05/15 14:57:24 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcpy(void *destination, const void *source, size_t n)
{
	size_t	i;

	i = 0;
	if (!destination && !source)
		return (0);
	while (n != 0)
	{
		((unsigned char*)destination)[i] = ((unsigned char*)source)[i];
		i++;
		n--;
	}
	return (destination);
}
