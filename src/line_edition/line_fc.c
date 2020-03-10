/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 01:07:48 by frameton          #+#    #+#             */
/*   Updated: 2020/03/10 01:08:05 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

void	swap_list(t_lstcontainer *list, t_fcparse *opt)
{
	t_list	*buf;

	if (!list || !list->firstelement || !opt)
		return ;
	buf = ft_lstgetfirst(list->firstelement);
	while (buf)
	{
		if (ft_strcmp(buf->content, opt->first) == 0)
		{
			ft_free(buf->content);
			buf->content = ft_strdup(opt->last);
		}
		buf = buf->next;
	}
}

char	*rebuild_line(t_lstcontainer *list)
{
	char	*new;
	t_list	*tmp;

	if (!list)
		return (NULL);
	tmp = ft_lstgetfirst(list->firstelement);
	new = NULL;
	while (tmp)
	{
		new = ft_strjoinfree(new, tmp->content, 1);
		tmp = tmp->next;
	}
	ft_freesplitlist(list);
	return (new);
}
