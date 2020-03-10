/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst2_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 22:43:48 by frameton          #+#    #+#             */
/*   Updated: 2020/03/10 19:16:57 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

void		free_tmp_export5(char ***tmp)
{
	free((*tmp)[0]);
	free(*tmp);
}

int			exec_export5(char ***tmp, char **av, t_struct *s, t_lst2 **l)
{
	*l = s->env;
	if ((*tmp = (char**)malloc(sizeof(**tmp) * 3)) == NULL)
	{
		ft_eputendl("export: warning: malloc error.");
		return (0);
	}
	if (((*tmp[0]) = ft_mstrcpy(NULL, av[1])) == NULL)
	{
		ft_eputendl("export: warning: malloc error");
		return (0);
	}
	return (1);
}

static int	e_cpt_2(t_struct *s, t_lst **l, int *c)
{
	while ((*l)->next)
		*l = (*l)->next;
	while (*l != s->lbg && check_whitespaces((*l)->c))
		*l = (*l)->prev;
	while (*l && (*l)->c != '{')
		*l = (*l)->prev;
	if (!*l || (*l)->prev->c != '$')
		return (0);
	*l = (*l)->next;
	s->l = *l;
	while (s->l && (*c = *c + 1))
		s->l = s->l->next;
	s->l = *l;
	return (1);
}

int			e_cpt(t_struct *s, t_comp **cmp, t_comp **bcmp)
{
	t_lst	*l;
	char	*line;
	int		c;
	t_lst2	*cpt;

	c = 0;
	l = s->lbg;
	line = NULL;
	cpt = s->env;
	if (!(e_cpt_2(s, &l, &c)))
		return (0);
	create_line(&line, s, 0, c);
	while (cpt)
	{
		if (!(ft_strncmp(line, cpt->varn, c)) && !(s_command_tab2(cpt->varn,
						&*cmp, &*bcmp, NULL)))
			return (sec_free(&line, 0));
		cpt = cpt->next;
	}
	if (!*bcmp)
		return (sec_free(&line, 0));
	s->cpt_p3 = 1;
	return (sec_free(&line, 1));
}

int			init_lst2_b4(char buf[701], t_lst **l, int *c)
{
	if (buf[*c] < 0 || buf[*c] > 127)
		return (1);
	if ((*l = malloc(sizeof(**l))) == NULL)
		return (-1);
	(*l)->c = buf[*c];
	(*l)->sel = 0;
	(*l)->next = NULL;
	return (2);
}
