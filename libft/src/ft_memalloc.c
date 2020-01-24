/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 09:55:25 by mabayle           #+#    #+#             */
/*   Updated: 2018/04/18 21:19:27 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*ret_str;

	ret_str = (void *)malloc(size * sizeof(size_t));
	if (ret_str == NULL)
		return (NULL);
	ft_bzero(ret_str, size);
	return (ret_str);
}
