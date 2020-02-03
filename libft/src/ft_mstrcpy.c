/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mstrcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 23:46:38 by frameton          #+#    #+#             */
/*   Updated: 2019/08/04 22:44:34 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_mstrcpy(char *dest, const char *src)
{
	char	*sa;
	int		c;

	c = 0;
	while (src[c])
		c++;
	if ((dest = (char*)malloc(sizeof(*dest) * (c + 1))) == NULL)
		return (NULL);
	sa = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (sa);
}
