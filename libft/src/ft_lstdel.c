/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 09:53:23 by mabayle           #+#    #+#             */
/*   Updated: 2019/02/25 18:04:46 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void		ft_lstdel(t_ftlst **alst, void (*del)(void *, size_t))
{
	t_ftlst	*node;
	t_ftlst	*next;

	node = *alst;
	if (alst == NULL || del == NULL)
		return ;
	while (node != NULL)
	{
		next = node->next;
		ft_lstdelone(&node, del);
		node = next;
	}
	*alst = NULL;
}
