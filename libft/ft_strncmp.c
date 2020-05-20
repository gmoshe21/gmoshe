/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.tr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 02:49:00 by gmoshe            #+#    #+#             */
/*   Updated: 2020/05/16 02:49:02 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	*str_1;
	unsigned char	*str_2;

	str_1 = (unsigned char*)str1;
	str_2 = (unsigned char*)str2;
	i = 0;
	while ((str_1[i] != '\0' && str_2[i] != '\0') && (n != 0))
	{
		if (str_1[i] != str_2[i])
			return (str_1[i] - str_2[i]);
		i++;
		n--;
	}
	if (!n)
		return (0);
	else
		return (str_1[i] - str_2[i]);
}
