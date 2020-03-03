/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 15:27:07 by frameton          #+#    #+#             */
/*   Updated: 2020/03/02 23:02:32 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_create(size_t *z, char ***tab, const char *s, char c)
{
	*tab = NULL;
	*z = ft_nbcword((char *)s, c);
	return (0);
}

static int	ft_create1(const char **s, const char *s1, char c)
{
	*s = ft_pfrontc((char *)s1, c);
	return (0);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i;
	int		i1;
	size_t	z;

	if (!(i1 = ft_create(&z, &tab, s, c)) && s)
	{
		if ((tab = (char**)malloc(sizeof(*tab) *
						(ft_nbcword((char *)s, c) + 1))) == NULL)
			return (NULL);
		while (z--)
		{
			i = ft_create1(&s, s, c);
			while (s[i] != c && s[i])
				i++;
			if ((tab[i1] = (char*)malloc(sizeof(**tab) * (i + 1))) == NULL)
				return (NULL);
			i = 0;
			while (*s != c && *s)
				tab[i1][i++] = *s++;
			tab[i1++][i] = '\0';
		}
		tab[i1] = 0;
	}
	return (tab);
}
