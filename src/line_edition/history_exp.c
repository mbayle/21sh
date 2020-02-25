/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 23:43:09 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 02:16:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/linedition.h"

void		free_lst(t_struct *s)
{
	t_lst	*del;

	while (s->lbg)
	{
		del = s->lbg->next;
		free(s->lbg);
		s->lbg = del;
	}
	s->lbg = NULL;
	s->tmp = NULL;
}

static void	last_command2(t_struct *s, t_htr *t, int *c)
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

int			last_command(t_struct *s, int c)
{
	t_htr	*t;

	t = s->h;
	free_lst(s);
	if (!s->h)
	{
		fp("fp", NULL);
		ft_2putstr("\n", RED"No command found.\n"WHITE);
		print_prompt_bis(s->prompt, s, 0);
		return (1);
	}
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
		last_command2(s, t, &c);
	}
	return (1);
}

int			check_number(char *line)
{
	if (!*line || *line != '!')
		return (0);
	line++;
	if (*line == '-')
		line++;
	while (*line)
	{
		if (!ft_isnum(*line))
			break ;
		line++;
	}
	if (*line)
		return (0);
	return (1);
}

int			history_exp(t_struct *s)
{
	char	*line;
	int		c;

	line = NULL;
	c = 0;
	if (!s->lbg && !s->tmp)
		return (0);
	if (!s->lbg)
		s->lbg = s->tmp;
	s->l = s->lbg;
	while (s->l && (c = c + 1))
		s->l = s->l->next;
	s->l = s->lbg;
	if (!(create_line(&line, s, 0, c)))
		return (0);
	if (!(ft_strcmp(line, "!!")))
		return (last_command(s, sec_free(&line, 0)));
	if (check_number(line))
		return (search_nbr_cmd(s, &line, 1));
	if (line[0] == '!')
		return (search_str_cmd(s, &line));
	return (sec_free(&line, 0));
}
