/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlenu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:26:05 by ymarcill          #+#    #+#             */
/*   Updated: 2020/02/20 00:19:59 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int		ft_occur(char const *s, char c)
{
	int occur;
	int i;

	i = 0;
	occur = 0;
	while (s && s[i])
	{
		if (s[i] == c)
			occur++;
		i++;
	}
	return (occur);
}

int		ft_strlenu(char *str)
{
	int				i;
	int				y;
	unsigned char	*tmp;

	i = 0;
	y = 0;
	tmp = (unsigned char*)str;
	if (str)
	{
		while (tmp[i])
		{
			if (tmp[i] >> 7 == 0b1)
			{
				if (tmp[i] >> 5 == 0b00000110)
					y--;
				else if (tmp[i] >> 4 == 0b00001110)
					y = y - 2;
				else if (tmp[i] >> 3 == 0b00011110)
					y = y - 3;
			}
			i++;
			y++;
		}
	}
	return (y);
}

char	*ft_strjoinfree(char *s1, char *s2)
{
	char	*tmp;

	if (s1 == NULL)
		return (NULL);
	tmp = ft_strdup(s1);
	if (!tmp)
		return (NULL);
	ft_strdel(&s1);
	s1 = ft_strjoin(tmp, s2);
	ft_strdel(&tmp);
	return (s1);
}

char	*ft_strjoinnf(char const *s1, char const *s2)
{
	char	*str;
	int		x;
	char	*tmp;

	if (!s1 || !(s2))
	{
		free((void*)s1);
		return (NULL);
	}
	x = ft_strlen(s2) + ft_strlen(s1);
	if (!(str = ft_strnew(x + 1)))
	{
		free((void*)s1);
		return (NULL);
	}
	tmp = str;
	tmp = ft_strcpy(tmp, s1);
	str = ft_strcat(tmp, s2);
	free((void*)s1);
	return (str);
}
