/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.tr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 21:30:34 by gmoshe            #+#    #+#             */
/*   Updated: 2020/05/20 21:30:37 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int						ft_len(char *s, char c)
{
	int					len;
	int					i;

	len = 0;
	i = 0;
	if (ft_strlen(s) == 0)
		return (len);
	if (s[0] == c)
		s++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i - 1] != c)
			len++;
		i++;
	}
	if (s[i] == '\0' && s[i - 1] != c)
		len++;
	return (len);
}

int						ft_len_str(char *s, int i, char c)
{
	int					x;

	x = 0;
	while (s[i] != c && s[i])
	{
		i++;
		x++;
	}
	return (x);
}

int						ft_str_i(char *s, char c, int x)
{
	int					i;
	int					j;

	i = 0;
	while (s[i] == c)
		i++;
	while (s[i] && x != 0)
	{
		j = 0;
		while (s[i] == c && s[i + 1] == c)
		{
			j++;
			i++;
		}
		if ((j != 0) || (s[i - 1] != c && s[i] == c && s[i + 1] != c))
			x--;
		if (s[i + 1] != c && s[i] == c && x == 0)
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

char					**ft_str_s(char *s, char **str, char c, int x)
{
	int					i;
	int					j;
	int					len;
	int					x1;

	x1 = x;
	i = ft_str_i(s, c, x);
	j = 0;
	len = ft_len_str(s, i, c);
	str[x1] = (char*)malloc(sizeof(char) * (len + 1));
	if (!str[x1])
	{
		while (str[x1])
			free(str[x1--]);
		return (NULL);
	}
	while (s[i] != c && s[i] != '\0')
	{
		str[x1][j] = s[i];
		j++;
		i++;
	}
	str[x1][j] = '\0';
	return (str);
}

char					**ft_split(char const *s, char c)
{
	int					len;
	char				**str;
	int					x;
	int					lens;

	if (s == NULL)
		return (NULL);
	x = 0;
	len = ft_len((char*)s, c);
	lens = len;
	if (!(str = (char**)malloc(sizeof(char*) * (lens + 1))))
		return (0);
	while (len-- != 0)
	{
		if (ft_str_s((char*)s, str, c, x) == NULL)
		{
			free(str);
			return (NULL);
		}
		x++;
	}
	str[lens] = NULL;
	return (str);
}
