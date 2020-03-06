/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 01:14:36 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 02:16:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

static int	edit_history2(t_lst *bg, int c, t_htr **new, t_htr **h)
{
	while (bg)
	{
		(*new)->name[c++] = bg->c;
		bg = bg->next;
	}
	(*new)->name[c] = '\0';
	(*new)->prev = NULL;
	if (!*h && c)
		(*new)->next = NULL;
	else
	{
		if (!c || strcmp((*new)->name, (*h)->name) == 0)
		{
			free((*new)->name);
			free(*new);
			return (1);
		}
		(*new)->next = *h;
		(*h)->prev = *new;
	}
	*h = *new;
	return (1);
}

int			edit_history(t_htr **h, t_lst *l, t_lst *bg, t_htr *new)
{
	int		c;

	c = 0;
	if (bg == NULL)
		return (1);
	while (l)
	{
		++c;
		l = l->next;
	}
	if ((new = malloc(sizeof(*new))) == NULL)
		return (0);
	if ((new->name = (char*)malloc(sizeof(*new->name) * (c + 1))) == NULL)
		return (0);
	while (bg && check_whitespaces(bg->c))
		bg = bg->next;
	return (edit_history2(bg, 0, &new, &*h));
}
