/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.tr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 02:50:45 by gmoshe            #+#    #+#             */
/*   Updated: 2020/05/16 03:03:36 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *str)
{
	char	*str_2;
	int		i;

	i = 0;
	str_2 = (char*)ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!(str_2))
		return (NULL);
	while (str[i])
	{
		str_2[i] = str[i];
		i++;
	}
	str_2[i] = '\0';
	return (str_2);
}
