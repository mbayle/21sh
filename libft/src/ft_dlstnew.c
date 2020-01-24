/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 03:10:08 by mabayle           #+#    #+#             */
/*   Updated: 2018/09/18 23:18:33 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

t_libnode	*ft_dlstnew(void const *content, size_t content_size)
{
	t_libnode *dlist;

	if (!(dlist = (t_libnode*)ft_memalloc(sizeof(t_libnode))))
		return (NULL);
	if (content)
	{
		if (!(dlist->content = (void*)ft_memalloc(content_size)))
			return (NULL);
		ft_memcpy(dlist->content, content, content_size);
		dlist->content_size = content_size;
	}
	else
	{
		dlist->content = NULL;
		dlist->content_size = 0;
	}
	dlist->lst_size = 1;
	dlist->prev = NULL;
	dlist->next = NULL;
	return (dlist);
}
