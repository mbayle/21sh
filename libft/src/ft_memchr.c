/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 09:55:51 by mabayle           #+#    #+#             */
/*   Updated: 2018/04/18 16:12:33 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptrs;
	unsigned char	ptrc;
	int				i;

	i = 0;
	ptrs = (unsigned char *)s;
	ptrc = (unsigned char)c;
	while (n--)
	{
		if (ptrs[i] == ptrc)
			return (ptrs + i);
		i++;
	}
	return (NULL);
}
