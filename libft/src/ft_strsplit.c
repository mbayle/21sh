/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 10:11:21 by mabayle           #+#    #+#             */
/*   Updated: 2019/07/22 04:43:01 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "libft.h"

int				ft_count_word(char const *s, char c)
{
	int	count;
	int	begin_word;

	begin_word = 0;
	count = 0;
	while (*s != '\0')
	{
		if (begin_word == 1 && *s == c)
			begin_word = 0;
		if (begin_word == 0 && *s != c)
		{
			begin_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static int		ft_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**ptr;
	int		nb_word;
	int		index;

	if (!s)
		return (NULL);
	index = 0;
	nb_word = ft_count_word(s, c);
	if (!(ptr = (char**)malloc(sizeof(char*) * (ft_count_word(s, c) + 1))))
		return (NULL);
	while (nb_word--)
	{
		while (*s == c && *s != '\0')
			s++;
		if (!(ptr[index] = ft_strsub(s, 0, ft_len(s, c))))
		{
			free(ptr);
			ptr = NULL;
			return (NULL);
		}
		s = s + ft_len(s, c);
		index++;
	}
	ptr[index] = NULL;
	return (ptr);
}
