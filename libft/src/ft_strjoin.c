/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 10:07:07 by mabayle           #+#    #+#             */
/*   Updated: 2019/07/22 08:47:54 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char					*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	u_i;
	unsigned int	u_j;
	char			*dest;

	u_i = 0;
	u_j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	dest = (char*)malloc(sizeof(*dest) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dest == NULL)
		return (NULL);
	while (s1[u_i] != '\0')
	{
		dest[u_i] = s1[u_i];
		u_i++;
	}
	while (s2[u_j] != '\0')
	{
		dest[u_i + u_j] = s2[u_j];
		u_j++;
	}
	dest[u_i + u_j] = '\0';
	return (dest);
}
