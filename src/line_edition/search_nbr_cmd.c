/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_nbr_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 23:41:53 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 02:16:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/linedition.h"

int			no_match_cmd(t_struct *s)
{
	free_lst(s);
	fp("bl", NULL);
	ft_putchar('\n');
	ft_putstr(FRED"No command found.\n"WHITE);
	print_prompt_bis(s->prompt, s, 0);
	return (1);
}

static void	change_lst_nbr2(t_struct *s, t_htr *t, int *c)
{
	s->tmp->next->sel = 0;
	s->tmp->next->next = NULL;
	s->tmp->next->prev = s->tmp;
	s->tmp->next->c = t->name[*c];
	s->tmp = s->tmp->next;
	(*c)++;
	if (!t->name[*c])
	{
		ft_putchar('\n');
		print_prompt_bis(s->prompt, s, 1);
		fp("le", "le");
		ft_putchar('>');
		fp("nd", NULL);
		s->l = s->lbg;
		while (s->l)
		{
			ft_putchar(s->l->c);
			s->l = s->l->next;
		}
		s->l = s->lbg;
	}
}

int			change_lst_nbr(t_htr *t, t_struct *s)
{
	int		c;

	c = 0;
	free_lst(s);
	if ((s->lbg = malloc(sizeof(*s->lbg))) == NULL)
		return (0);
	s->lbg->c = t->name[c++];
	s->lbg->sel = 0;
	s->lbg->prev = NULL;
	s->lbg->next = NULL;
	s->tmp = s->lbg;
	while (t->name[c])
	{
		if ((s->tmp->next = malloc(sizeof(*s->tmp))) == NULL)
			return (0);
		change_lst_nbr2(s, t, &c);
	}
	return (1);
}

static int	search_nbr_cmd2(t_struct *s, t_htr *t, int c, int nbr)
{
	nbr = nbr * -1;
	while (t && c != nbr)
	{
		++c;
		t = t->next;
	}
	if (!t)
		return (no_match_cmd(s));
	return (change_lst_nbr(t, s));
}

int			search_nbr_cmd(t_struct *s, char **line, int c)
{
	int		nbr;
	t_htr	*t;
	char	*l;

	t = s->h;
	l = *line;
	l++;
	nbr = ft_atoi(l);
	sec_free(line, 0);
	if (nbr == 0)
		return (no_match_cmd(s));
	if (nbr > 0)
	{
		while (t->next)
			t = t->next;
		while (t && c < nbr)
		{
			++c;
			t = t->prev;
		}
		if (!t)
			return (no_match_cmd(s));
		return (change_lst_nbr(t, s));
	}
	return (search_nbr_cmd2(s, t, c, nbr));
}
