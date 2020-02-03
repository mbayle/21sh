/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitws.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 00:22:19 by frameton          #+#    #+#             */
/*   Updated: 2019/08/21 00:22:21 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define W ft_nbword((char *)s)

#include "libft.h"

static int	ft_create(size_t *z, char ***tab, const char *s)
{
	*tab = NULL;
	*z = W;
	return (0);
}

static int	ft_create1(const char **s, const char *s1)
{
	*s = ft_pfrontws((char *)s1);
	return (0);
}

char		**ft_splitws(char const *s)
{
	char	**tab;
	int		i;
	int		i1;
	size_t	z;

	i1 = ft_create(&z, &tab, s);
	if (s)
	{
		if ((tab = (char**)malloc(sizeof(*tab) * (W + 1))) == NULL)
			return (NULL);
		while (z--)
		{
			i = ft_create1(&s, s);
			while (!(check_whitespaces(s[i])) && s[i])
				i++;
			if ((tab[i1] = (char*)malloc(sizeof(**tab) * (i + 1))) == NULL)
				return (NULL);
			i = 0;
			while (!(check_whitespaces(*s)) && *s)
				tab[i1][i++] = *s++;
			tab[i1++][i] = '\0';
		}
		tab[i1] = 0;
	}
	return (tab);
}
