/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:24:57 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 22:33:19 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

void		clr_shell(int i)
{
	if (!i)
		ft_putstr(BLUE);
	if (i == 1)
		ft_putstr(FBLUE);
	if (i == 2)
		ft_putstr(RED);
	if (i == 3)
		ft_putstr(FRED);
	if (i == 4)
		ft_putstr(GREEN);
	if (i == 5)
		ft_putstr(FGREEN);
	if (i == 6)
		ft_putstr(YELLOW);
	if (i == 7)
		ft_putstr(FYELLOW);
	if (i == 8)
		ft_putstr(MAGENTA);
	if (i == 9)
		ft_putstr(FMAGENTA);
	if (i == 10)
		ft_putstr(CYAN);
	if (i == 11)
		ft_putstr(FCYAN);
	if (i == 12)
		ft_putstr(WHITE);
	if (i == 13)
		ft_putstr(GREY);
}

static void	print_prompt_bis4(t_struct st, int i)
{
	g_lined ? st.cpt = g_lined->cpt : 0;
	clr_shell(st.clr);
	ft_putstr("~ ");
	if (st.set_cpt)
	{
		ft_putstr(GREEN);
		ft_putchar('>');
		ft_putnbr(st.cpt);
		ft_putchar('<');
	}
	else
	{
		ft_putchar('-');
		ft_putnbr(st.cpt);
		ft_putchar('-');
	}
	if (st.ci && !i)
		ft_putstr(RED" > "WHITE);
	if (st.ci && i)
		ft_putstr(GREEN" > "WHITE);
	if (!st.ci)
	{
		clr_shell(st.clr);
		ft_putstr(" > "WHITE);
	}
}

static void	print_prompt_bis5(char *pw, char *h)
{
	char	*tmp;

	tmp = pw;
	if (pw)
	{
		h = pw;
		pw = ft_pstrback(pw);
		while (*pw != '/')
			pw--;
		if (pw != h)
			pw++;
		ft_putstr(pw);
	}
	else
		ft_putstr("42sh");
	ft_putstr(" ");
	pw = tmp;
}

static void	print_prompt_bis3(t_struct st, char *h, char **pw, int i)
{
	g_lined ? st.cpt = g_lined->cpt : 0;
	if ((pw && h) && strcmp(h, *pw) == 0)
		print_prompt_bis4(st, i);
	else
	{
		clr_shell(st.clr);
		print_prompt_bis5(*pw, h);
		if (st.set_cpt)
		{
			ft_putstr(GREEN);
			ft_putchar('>');
			ft_putnbr(st.cpt);
			ft_putchar('<');
		}
		else
		{
			ft_putchar('-');
			ft_putnbr(st.cpt);
			ft_putchar('-');
		}
		(!i) ? ft_putstr(RED) : ft_putstr(GREEN);
		(!st.ci) ? clr_shell(st.clr) : 0;
		ft_putstr(" > "WHITE);
	}
	sec_free(pw, 0);
}

int			print_prompt_bis(int p, t_struct *s, int i)
{
	char	*h;
	char	*pw;
	t_lst2	*st;
	t_lst2	*sa;

	(void)p;
	st = (*s).env;
	h = NULL;
	pw = NULL;
	sa = st;
	pw = getcwd(pw, PATH_MAX);
	while (st)
	{
		if (ft_strcmp(st->varn, "HOME") == 0)
			h = st->var;
		st = st->next;
	}
	st = sa;
	print_prompt_bis3(*s, h, &pw, i);
	return (1);
}
