/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 10:09:40 by mabayle           #+#    #+#             */
/*   Updated: 2018/04/16 17:52:15 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strnew(size_t size)
{
	char	*return_str;

	return_str = (char*)malloc((size + 1) * sizeof(char));
	if (return_str == NULL)
		return (NULL);
	ft_bzero(return_str, size);
	return_str[size] = '\0';
	return (return_str);
}
