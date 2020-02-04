/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_welcom2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:30:11 by frameton          #+#    #+#             */
/*   Updated: 2020/01/25 00:31:02 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cline(int m)
{
	tputs(tgetstr("cr", NULL), 1, ft_ptchar);
	tputs(tgetstr("ce", NULL), 1, ft_ptchar);
	tputs(tgetstr("up", NULL), 1, ft_ptchar);
	bar(m - 5, 0);
	tputs(tgetstr("do", NULL), 1, ft_ptchar);
}

void	upl(int m)
{
	tputs(tgetstr("up", NULL), 1, ft_ptchar);
	cline(m);
}

void	fp(char *s, char *s2)
{
	tputs(tgetstr(s, NULL), 1, ft_ptchar);
	if (s2)
		tputs(tgetstr(s2, NULL), 1, ft_ptchar);
}

void	do_m(int m)
{
	tputs(tgetstr("do", NULL), 1, ft_ptchar);
	ft_vmarge(m);
}

void	ft_putstr_anim(char *s, int c)
{
	while (c--)
	{
		ft_putchar(*s);
		s++;
		usleep(20000);
	}
}
