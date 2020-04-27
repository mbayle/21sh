/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wlcm_msg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 23:01:08 by frameton          #+#    #+#             */
/*   Updated: 2020/04/27 20:09:54 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

static int		wlcm_ws(int *m, int *s)
{
	struct winsize	sz;

	ioctl(0, TIOCGWINSZ, &sz);
	*s = sz.ws_col;
	if (sz.ws_col < 60)
		return (0);
	*m = sz.ws_col - 54;
	*m = *m / 2;
	return (1);
}

void			wlcm_msg(t_struct *st)
{
	int		m;
	int		s;
	int		c;

	m = 0;
	s = 0;
	c = 0;
	if (!wlcm_ws(&m, &s))
		return ;
	fp("cl", NULL);
	ft_putchar('\n');
	clr_shell(st->clr);
	while (c < s && (c = c + 1))
		ft_putchar('-');
	es7(WHITE"Info: enter the help command to know the basic commands", m);
	ft_putchar('\n');
	c = 0;
	clr_shell(st->clr);
	while (c < s && (c = c + 1))
		ft_putchar('-');
	ft_putstr("\n\n");
	print_prompt_bis(st->prompt, st, 0);
}
