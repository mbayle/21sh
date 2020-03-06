/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edl2_move_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:59:12 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 02:16:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int		move_word_r_w(t_lst **tmp)
{
	while ((*tmp)->next && check_whitespaces((*tmp)->next->c))
	{
		*tmp = (*tmp)->next;
		tputs(tgetstr("nd", NULL), 1, ft_ptchar);
	}
	if (!((*tmp)->next))
		tputs(tgetstr("ei", NULL), 1, ft_ptchar);
	else
		tputs(tgetstr("im", NULL), 1, ft_ptchar);
	return (1);
}

int		move_word_r(t_lst **tmp)
{
	if ((*tmp)->next)
	{
		*tmp = (*tmp)->next;
		tputs(tgetstr("nd", NULL), 1, ft_ptchar);
	}
	if (*tmp && check_whitespaces((*tmp)->c))
		return (move_word_r_w(tmp));
	while ((*tmp)->next && !(check_whitespaces((*tmp)->next->c)))
	{
		*tmp = (*tmp)->next;
		tputs(tgetstr("nd", NULL), 1, ft_ptchar);
	}
	while ((*tmp)->next && check_whitespaces((*tmp)->next->c))
	{
		*tmp = (*tmp)->next;
		tputs(tgetstr("nd", NULL), 1, ft_ptchar);
	}
	if (!((*tmp)->next))
		tputs(tgetstr("ei", NULL), 1, ft_ptchar);
	else
		tputs(tgetstr("im", NULL), 1, ft_ptchar);
	return (1);
}

int		edl2_move_word_w(t_lst **lbg, t_lst **tmp)
{
	while ((*tmp)->prev && check_whitespaces((*tmp)->prev->c))
	{
		*tmp = (*tmp)->prev;
		tputs(tgetstr("le", NULL), 1, ft_ptchar);
	}
	while ((*tmp)->prev && !(check_whitespaces((*tmp)->prev->c)))
	{
		*tmp = (*tmp)->prev;
		tputs(tgetstr("le", NULL), 1, ft_ptchar);
	}
	if ((*tmp)->prev)
	{
		*tmp = (*tmp)->prev;
		tputs(tgetstr("le", NULL), 1, ft_ptchar);
	}
	if (!((*tmp)->prev))
	{
		*lbg = NULL;
		tputs(tgetstr("le", NULL), 1, ft_ptchar);
	}
	tputs(tgetstr("im", NULL), 1, ft_ptchar);
	return (1);
}

int		edl2_move_word(t_lst **lbg, t_lst **tmp, int c)
{
	if (c == 66 || c == 65)
		return (1);
	if (c == 67)
		return (move_word_r(tmp));
	if (*tmp && check_whitespaces((*tmp)->c))
		return (edl2_move_word_w(lbg, tmp));
	while ((*tmp)->prev && !(check_whitespaces((*tmp)->prev->c)))
	{
		*tmp = (*tmp)->prev;
		tputs(tgetstr("le", NULL), 1, ft_ptchar);
	}
	if ((*tmp)->prev)
	{
		*tmp = (*tmp)->prev;
		tputs(tgetstr("le", NULL), 1, ft_ptchar);
	}
	if (!((*tmp)->prev))
	{
		*lbg = NULL;
		tputs(tgetstr("le", NULL), 1, ft_ptchar);
	}
	tputs(tgetstr("im", NULL), 1, ft_ptchar);
	return (1);
}
