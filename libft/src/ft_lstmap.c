/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 09:53:53 by mabayle           #+#    #+#             */
/*   Updated: 2018/04/21 15:16:56 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ftlst	*ft_lstmap(t_ftlst *lst, t_ftlst *(*f)(t_ftlst *elem))
{
	t_ftlst	*first;
	t_ftlst	*new_lst;
	t_ftlst	*f_lst;

	if (!lst || !f)
		return (NULL);
	f_lst = f(lst);
	if (!(new_lst = ft_lstnew(f_lst->content, f_lst->content_size)))
		return (NULL);
	first = new_lst;
	lst = lst->next;
	while (lst)
	{
		f_lst = f(lst);
		if (!(new_lst->next = ft_lstnew(f_lst->content, f_lst->content_size)))
			return (NULL);
		new_lst = new_lst->next;
		lst = lst->next;
	}
	return (first);
}
