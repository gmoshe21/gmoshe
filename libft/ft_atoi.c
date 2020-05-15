/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.tr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 16:20:27 by gmoshe            #+#    #+#             */
/*   Updated: 2020/05/15 16:20:30 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_atoi(const char *str)
{
	int				i;
	int				znak;
	unsigned long	ch;

	i = 0;
	ch = 0;
	znak = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			znak = -1;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		ch = ch * 10;
		ch = ch + (str[i++] - 48);
		if (znak < 0 && ch > 9223372036854775807)
			return (0);
		if (znak > 0 && ch > 9223372036854775807)
			return (-1);
	}
	return ((int)(ch * znak));
}
