/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:54:59 by frameton          #+#    #+#             */
/*   Updated: 2020/03/07 20:53:41 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

static void	init_lst_b(struct termios *term, t_struct *s)
{
	static int		wlcm;

	(void)term;
	print_prompt(s->prompt, s, 0);
	sec_free(&s->cmd, 0);
	s->nl = 0;
	if (!wlcm && isatty(0) && (wlcm = 1) && s->env_i)
		welcome(*s);
	fp("ve", NULL);
}

static void	init_lst_b2(t_struct *s, char buf[6], int ret)
{
	if (buf[0] == 12 && ret == 1 && (buf[0] = '\n'))
	{
		tputs(tgetstr("cl", NULL), 1, ft_ptchar);
		free_lst(s);
	}
	else
		write(1, "\n", 1);
	if (buf[0] == 9 && !s->lbg && !s->tmp)
	{
		tputs(tgetstr("cr", NULL), 1, ft_ptchar);
		tputs(tgetstr("up", NULL), 1, ft_ptchar);
		tputs(tgetstr("dl", NULL), 1, ft_ptchar);
		write(1, "\n", 1);
	}
	tputs(tgetstr("ei", NULL), 1, ft_ptchar);
	if (!s->lbg && s->tmp)
		s->lbg = s->tmp;
}

static int	init_lst_b3(t_struct *s, struct termios *term, int i)
{
	int		c;

	(void)*term;
	c = 0;
	s->l = s->lbg;
	s->nl = 0;
	while (s->l && (c = c + 1))
		s->l = s->l->next;
	s->l = s->lbg;
	if (c && !(create_line(&s->cmd, s, 0, c)))
		return (-1);
	while (s->tmp && s->tmp->next)
	{
		s->tmp = s->tmp->next;
		if (s->tmp && s->tmp->line > s->tmp->prev->line)
			tputs(tgetstr("do", NULL), 1, ft_ptchar);
	}
	if (s->ctrl_d)
	{
		sec_free(&s->cmd, 0);
		if (!(s->cmd = ft_mstrcpy(NULL, "exit")))
			return (0);
	}
	s->ctrl_d = 0;
	return (i);
}

int			init_lst_b4(t_struct *s, struct winsize *sz, char buf[701])
{
	if (isatty(0) == 0)
	{
		s->cmd = ft_strdupt(buf, '\n');
		return (0);
	}
	ioctl(0, TIOCGWINSZ, sz);
	return (1);
}

int			init_lst(t_struct *s, int i, int r, int ret)
{
	char			buf[701];
	int				sret;
	struct winsize	sz;
	struct termios	term;

	init_lst_b(&term, s);
	while (!s->ctrl_d && r != 3 && (ret = read(0, buf, 700)))
	{
		sret = ret;
		while (sret < 701)
			buf[sret++] = '\0';
		if (!init_lst_b4(s, &sz, buf))
			return (1);
		if ((s->col = sz.ws_col) && ((buf[0] == '\n' && !history_exp(s, 0, NULL)
					&& check_quotes(s, buf)) || (buf[0] == 12 && ret == 1)))
			break ;
		if (!(r = recup_stdin(&*s, buf, &i, ret)))
			return (0);
	}
	init_lst_b2(s, buf, ret);
	if (buf[0] != '\n' && r < 3)
		return (init_lst_b3(s, &term, 2));
	if (s->lbg && !(edit_history(&s->h, s->lbg, s->lbg, NULL)))
		return (0);
	return (init_lst_b3(s, &term, 1));
}
