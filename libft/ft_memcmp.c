/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.tr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 14:58:01 by gmoshe            #+#    #+#             */
/*   Updated: 2020/05/15 14:58:04 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *arr1, const void *arr2, size_t n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n--;
		if (((unsigned char*)arr1)[i] != ((unsigned char*)arr2)[i])
			return (((unsigned char*)arr1)[i] - ((unsigned char*)arr2)[i]);
		i++;
	}
	return (0);
}
