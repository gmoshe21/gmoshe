/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.tr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 03:06:18 by gmoshe            #+#    #+#             */
/*   Updated: 2020/05/16 03:06:21 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_lenn(int n)
{
	int				i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * (-1);
		i++;
	}
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char				ft_char(int n)
{
	char			x;

	x = 0;
	n = n % 10;
	while (n != 0)
	{
		x++;
		n--;
	}
	return (x + '0');
}

void				*ft_r(int n)
{
	unsigned int	r;
	char			*str;

	r = n;
	if (n < 0)
		r = -n;
	if (r >= 2147483648)
	{
		str = (char*)ft_calloc(12, sizeof(char));
		if (!str)
			return (NULL);
		ft_strlcpy(str, "-2147483648", 12);
		return (str);
	}
	return (NULL);
}

char				*ft_itoa(int n)
{
	char			*str;
	int				len;
	char			x;

	x = '-';
	len = ft_lenn(n) - 1;
	if ((str = ft_r(n)) != NULL)
		return (str);
	str = (char*)ft_calloc(len + 2, sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '0';
	if (n == 0)
		return (str);
	if (n < 0)
	{
		str[0] = x;
		n = n * (-1);
	}
	while (n != 0)
	{
		str[len--] = ft_char(n);
		n = n / 10;
	}
	return (str);
}
