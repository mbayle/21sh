/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 09:56:43 by mabayle           #+#    #+#             */
/*   Updated: 2018/06/12 04:30:00 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char *s_src;
	char *s_dst;

	s_src = (char*)src;
	s_dst = (char*)dst;
	if (s_src < s_dst)
	{
		s_src = s_src + len - 1;
		s_dst = s_dst + len - 1;
		while (len > 0)
		{
			*s_dst-- = *s_src--;
			len--;
		}
	}
	else
	{
		while (len > 0)
		{
			*s_dst++ = *s_src++;
			len--;
		}
	}
	return (dst);
}
