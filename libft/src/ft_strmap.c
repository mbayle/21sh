/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 10:08:24 by mabayle           #+#    #+#             */
/*   Updated: 2018/04/19 12:46:41 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	char	*return_str;

	i = 0;
	if (!s || !f)
		return (NULL);
	if (!(return_str = ft_strnew(sizeof(char) * ft_strlen(s))))
		return (NULL);
	while (s[i] != '\0')
	{
		return_str[i] = f(s[i]);
		i++;
	}
	return (return_str);
}
