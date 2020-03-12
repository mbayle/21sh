/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setcpt3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:55:45 by frameton          #+#    #+#             */
/*   Updated: 2020/03/12 13:15:37 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

static void	exec_setcpt2_b(t_struct *s, int ret, int m)
{
	while (ret--)
		tputs(tgetstr("le", NULL), 1, ft_ptchar);
	ft_putnbr(s->cpt);
	exec_setcpt7(s);
	fp("le", "sc");
	ft_putstr("\n");
	ft_marge(m);
	ft_putstr(CYAN"_________________________________________________________");
	ft_putendl("___________________________"WHITE);
	tputs(tgetstr("rc", NULL), 1, ft_ptchar);
}

void		exec_setcpt2(t_struct *s, int m)
{
	int		ret;

	ft_marge(m + 9);
	ft_putendl("Lvl 5 : Automatic completion, effective with multiple matches");
	ft_putstr("\n\n");
	es9("The valid command indicator doesn't work with level 1", m + 15);
	ft_marge(m);
	ft_putstr("                             42sh ");
	ft_2putstr(RED"> ", WHITE"l     42sh ");
	ft_2putstr(GREEN"> ", WHITE"ls\n\n");
	es9("The paste option does not work with levels 4 and 5\n", m + 15);
	ft_marge(m + 10);
	ft_putendl("For a quick change in the completion level, use fn + < or >\n");
	ft_mputstr(WHITE
			"                        Current level of completion : "MAGENTA, m);
	ft_putnbr(s->cpt);
	ft_putstr("\n\n\n");
	ft_mputstr(WHITE
			"                Choose the level of completion you want ("CYAN, m);
	ft_2putstr("1 - 5", WHITE")\n\n");
	ft_mputstr("                                     <  ", m);
	ft_putstr("   >"MAGENTA);
	ret = 4;
	exec_setcpt2_b(s, ret, m);
}

void		exec_setcpt4(t_struct *s)
{
	fp("sc", "le");
	fp("le", "le");
	ft_putstr(WHITE"<");
	tputs(tgetstr("rc", NULL), 1, ft_ptchar);
	if (s->cpt == 4)
	{
		fp("sc", "nd");
		fp("nd", "nd");
		ft_putstr(WHITE" "MAGENTA);
		tputs(tgetstr("rc", NULL), 1, ft_ptchar);
	}
	if (s->cpt == 1)
	{
		fp("sc", "le");
		fp("le", "le");
		ft_putstr(WHITE"<"MAGENTA);
		tputs(tgetstr("rc", NULL), 1, ft_ptchar);
	}
	if (s->cpt < 5)
		s->cpt = s->cpt + 1;
	else
		tputs(tgetstr("bl", NULL), 1, ft_ptchar);
}

void		exec_setcpt5(t_struct *s)
{
	if (s->cpt > 2)
	{
		fp("sc", "le");
		fp("le", "le");
		ft_putstr(WHITE"<");
		tputs(tgetstr("rc", NULL), 1, ft_ptchar);
	}
	if (s->cpt == 5)
	{
		fp("sc", "nd");
		fp("nd", "nd");
		ft_putstr(WHITE">"MAGENTA);
		tputs(tgetstr("rc", NULL), 1, ft_ptchar);
	}
	if (s->cpt > 1)
		s->cpt = s->cpt - 1;
	else
		tputs(tgetstr("bl", NULL), 1, ft_ptchar);
}
