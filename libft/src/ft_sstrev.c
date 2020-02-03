/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 23:50:43 by frameton          #+#    #+#             */
/*   Updated: 2019/08/03 23:50:45 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_sstrev(char **s, int c)
{
	int		d;
	int		f;
	char	*tmp;

	d = c;
	f = c;
	tmp = NULL;
	if (!(s[c]))
		return (s);
	while (s[f])
		f++;
	f--;
	while (d < f)
	{
		tmp = s[d];
		s[d] = s[f];
		s[f] = tmp;
		d++;
		f--;
	}
	return (s);
}
