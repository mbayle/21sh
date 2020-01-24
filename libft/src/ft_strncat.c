/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 10:08:48 by mabayle           #+#    #+#             */
/*   Updated: 2018/04/18 15:07:44 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t nb)
{
	char	*p_dest;

	p_dest = dest;
	while (*p_dest != '\0')
	{
		p_dest++;
	}
	while (*src != '\0' && nb > 0)
	{
		*p_dest = *src;
		p_dest++;
		src++;
		nb--;
	}
	*p_dest = '\0';
	return (dest);
}
