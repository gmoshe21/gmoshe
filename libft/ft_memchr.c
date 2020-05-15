/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.tr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 14:59:54 by gmoshe            #+#    #+#             */
/*   Updated: 2020/05/15 14:59:58 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *arr, int c, size_t n)
{
	char	j;
	char	i;

	i = 0;
	while (c != 0 && c > 0)
	{
		c--;
		i++;
	}
	while (c != 0 && c < 0)
	{
		c++;
		i--;
	}
	while (n != 0)
	{
		j = *((char*)arr);
		if (j == i)
			return ((void*)arr);
		arr++;
		n--;
	}
	return (NULL);
}
