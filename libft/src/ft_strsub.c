/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 10:12:03 by mabayle           #+#    #+#             */
/*   Updated: 2018/04/20 02:55:23 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*return_str;
	size_t	i;

	i = 0;
	return_str = ft_strnew(sizeof(char) * len);
	if (s == NULL)
		return (NULL);
	if (return_str == NULL)
		return (NULL);
	while (len-- && *s)
	{
		return_str[i] = s[start + i];
		i++;
	}
	return (return_str);
}
