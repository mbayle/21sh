/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_str_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 23:42:26 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 02:16:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/linedition.h"

int		search_str_cmd(t_struct *s, char **line)
{
	int		c;
	char	*l;
	t_htr	*t;

	l = *line;
	t = s->h;
	l++;
	c = ft_strlen(l);
	if (!*l)
		return (sec_free(line, 0));
	while (t)
	{
		if (!ft_strncmp(l, t->name, c))
			break ;
		t = t->next;
	}
	if (!t)
		return (no_match_cmd(s));
	return (change_lst_nbr(t, s));
}
