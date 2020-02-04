/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_welcom.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:31:18 by frameton          #+#    #+#             */
/*   Updated: 2020/01/25 00:31:19 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sleep(int i)
{
	if (i)
		usleep(50000);
	if (!i)
		usleep(10000);
}

void	ft_vmarge(int m)
{
	while (m--)
		tputs(tgetstr("nd", NULL), 1, ft_ptchar);
}

void	es8(int m, char *s)
{
	ft_sleep(0);
	tputs(tgetstr("do", NULL), 1, ft_ptchar);
	ft_vmarge(m);
	ft_putstr(s);
}

void	bar(int m, int i)
{
	int		c;

	c = 90;
	ft_marge(m);
	while (c--)
	{
		ft_putchar('_');
		if (i)
			usleep(5000);
	}
}

void	rbar(int m)
{
	int		c;

	c = 90;
	tputs(tgetstr("up", NULL), 1, ft_ptchar);
	tputs(tgetstr("cr", NULL), 1, ft_ptchar);
	ft_marge(m - 5);
	while (c--)
	{
		ft_putchar(' ');
		usleep(5000);
	}
}
