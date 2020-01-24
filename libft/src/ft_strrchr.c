/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 10:10:28 by mabayle           #+#    #+#             */
/*   Updated: 2018/04/16 10:18:55 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if (s == NULL)
		return (NULL);
	if (c < 0 || c > 255 || c == '\0')
		return (char *)(s + i);
	while (s[i] != (char)c && i >= 0)
		--i;
	if (i < 0)
		return (NULL);
	return (char *)(s + i);
}
