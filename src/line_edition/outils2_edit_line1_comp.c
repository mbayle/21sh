/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils2_edit_line1_comp.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 22:14:07 by frameton          #+#    #+#             */
/*   Updated: 2020/02/03 22:14:37 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_lst_comp_tab(t_struct s)
{
	int		c;
	t_lst	*l;

	c = 0;
	l = s.lbg;
	while (l->next)
		l = l->next;
	while (l != s.lbg && check_whitespaces(l->c))
		l = l->prev;
	while (l != s.lbg && !check_whitespaces(l->c))
		l = l->prev;
	if (check_whitespaces(l->c))
		l = l->next;
	while (l && !check_whitespaces(l->c))
	{
		++c;
		l = l->next;
	}
	return (c);
}
