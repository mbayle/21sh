/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 19:31:45 by ymarcill          #+#    #+#             */
/*   Updated: 2020/04/22 19:31:47 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int		until_c(char *str, char c)
{
	int	i;

	i = ft_strlen(str);
	while (i >= 0 && str[i] != c)
		i--;
	return (i);
}

int		from_c(char *str, char c)
{
	int	i;
	int	y;

	i = ft_strlen(str);
	y = 0;
	while (i >= 0 && str[i] != c)
		i--;
	while (str[i++])
		y++;
	return (y);
}

char	*ft_strdupn(char *str, char c)
{
	char	*dst;
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(str);
	while (str && i >= 0)
	{
		if (str[i] == c)
		{
			dst = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
			while (str[++i])
				dst[j++] = str[i];
			dst[j] = '\0';
			return (dst);
		}
		i--;
	}
	return (NULL);
}

char	*ft_strldup(char *str, char c)
{
	char	*dst;
	int		i;
	int		j;
	int		index;

	j = 0;
	i = ft_strlen(str);
	while (str && i >= 0)
	{
		if (str[i] == c)
		{
			index = i;
			i = 0;
			dst = malloc(sizeof(char) * (ft_strlen(str) + 1));
			while (i <= index)
				dst[j++] = str[i++];
			dst[j] = '\0';
			return (dst);
		}
		i--;
	}
	return (NULL);
}

char	*ft_strdupt(char *str, char c)
{
	int		i;
	int		y;
	char	*dst;

	i = 0;
	y = 0;
	if (!str || !(dst = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	while (str[i] && str[i] != c)
		dst[y++] = str[i++];
	dst[y] = '\0';
	return (dst);
}
