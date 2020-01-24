/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 09:53:44 by mabayle           #+#    #+#             */
/*   Updated: 2018/04/16 09:53:47 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void		ft_lstiter(t_ftlst *lst, void (*f)(t_ftlst *elem))
{
	t_ftlst	*next;

	if (lst == NULL || f == NULL)
		return ;
	while (lst != NULL)
	{
		next = lst->next;
		f(lst);
		lst = next;
	}
}
