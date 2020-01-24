/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 09:54:16 by mabayle           #+#    #+#             */
/*   Updated: 2019/02/25 18:05:20 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

t_ftlst		*ft_lstnew(void const *content, size_t content_size)
{
	t_ftlst	*list;

	if (!(list = (t_ftlst*)ft_memalloc(sizeof(t_ftlst))))
		return (NULL);
	if (content)
	{
		if (!(list->content = (void*)ft_memalloc(content_size)))
			return (NULL);
		ft_memcpy(list->content, content, content_size);
		list->content_size = content_size;
	}
	else
	{
		list->content = NULL;
		list->content_size = 0;
	}
	list->next = NULL;
	return (list);
}
