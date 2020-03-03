/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 23:43:09 by frameton          #+#    #+#             */
/*   Updated: 2020/03/03 22:09:01 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

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

static int	history_exp2(t_struct *s, char **tmp, char **line)
{
	int		c;

	c = 0;
	while (**tmp)
	{
		if (!(ft_strncmp("!!", *tmp, 2)))
			c = last_command(line, tmp, s, 0);
		else if (*(*tmp + 1) && **tmp == '!' && (ft_isnum(*(*tmp + 1))
					|| *(*tmp + 1) == '-'))
			c = search_nbr_cmd(s, line, tmp, 1);
		else if (*(*tmp + 1) && **tmp == '!'
				&& !check_whitespaces(*(*tmp + 1)))
			c = search_str_cmd(s, line, tmp, 0);
		if (c == -1)
			return (0);
		(*tmp)++;
	}
	return (1);
}

static void	mod_lst2(t_struct *s, char *l)
{
	s->tmp->next->sel = 0;
	s->tmp->next->next = NULL;
	s->tmp->next->prev = s->tmp;
	s->tmp->next->c = *l;
	s->tmp = s->tmp->next;
	l++;
	if (!*l)
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

static int	mod_lst(char *l, t_struct *s, char **del)
{
	free_lst(s);
	if ((s->lbg = malloc(sizeof(*s->lbg))) == NULL)
		return (0);
	s->lbg->c = *l++;
	s->lbg->sel = 0;
	s->lbg->prev = NULL;
	s->lbg->next = NULL;
	s->tmp = s->lbg;
	while (*l)
	{
		if ((s->tmp->next = malloc(sizeof(*s->tmp))) == NULL)
			return (0);
		mod_lst2(s, l);
		l++;
	}
	sec_free(del, 0);
	return (1);
}

int			history_exp(t_struct *s, int c, char *line)
{
	char	*tmp;

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
	tmp = line;
	while (*tmp && *tmp != '!')
	{
		tmp++;
		if (*tmp == '!' && (check_whitespaces(*(tmp + 1)) || *(tmp + 1) == '='))
			tmp++;
	}
	if (!*tmp || !(*(tmp + 1)))
		return (sec_free(&line, 0));
	history_exp2(s, &tmp, &line);
	mod_lst(line, s, &line);
	return (1);
}
