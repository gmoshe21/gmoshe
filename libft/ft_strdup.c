/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.tr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 15:13:35 by gmoshe            #+#    #+#             */
/*   Updated: 2020/05/15 15:16:00 by student          ###   ########.fr       */
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
