#include "minishell.h"

int			putchar_completion2(t_struct *s, char c)
{
	t_lst	*l;

	l = NULL;
	if ((l = malloc(sizeof(*l))) == NULL)
		return (0);
	l->c = c;
	l->next = NULL;
	l->prev = s->tmp;
	l->line = 0;
	l->plc = 0;
	l->sel = 0;
	s->tmp->next = l;
	s->tmp = s->tmp->next;
	return (1);
}

int			putchar_completion(t_struct *s, t_htr **bcom, char *line, int c)
{
	t_htr	*com;

	com = *bcom;
	if (c < 2 || !com)
		return (0);
	line = create_line_comp(line, com, *bcom, c);
	if (c == (int)ft_strlen(line))
		return (1);
	while (c--)
		line++;
	if (s->cpt == 2 || s->cpt == 3)
	{
		s->comp.name = line;
		s->comp.sz = ft_strlen(line);
	}
	else
	{
		while (*line)
			if (!(putchar_completion2(s, *line++)))
				return (-1);
	}
	return (2);
}

void		free_bcom(t_struct *s)
{
	t_htr	*del;

	del = NULL;
	while (s->bcom)
	{
		del = s->bcom;
		free(del->name);
		free(del);
		s->bcom = s->bcom->next;
	}
	s->com = NULL;
	s->bcom = NULL;
}

int			completion_commands(char ***path, int c, t_struct *s, int i)
{
	char		*line;
	t_lst		*tmp;
	char		**del;

	i = 0;
	s->l = s->lbg;
	del = *path;
	free_bcom(s);
	if (!(check_whitespaces(s->tmp->c)))
		check_part_comp2(&*s);
	tmp = s->l;
	while (s->l && (c = c + 1))
		s->l = s->l->next;
	s->l = tmp;
	if (!c)
		return (1);
	if (!(create_line(&line, &*s, 0, c)))
		return (-1);
	if (!(s->com = create_lst_comp(&*path, &s->bcom, line, s->l)))
		return (1);
	s->bcom = char_class(s->bcom, s->bcom);
	s->l = s->lbg;
	if ((s->bcom->next && s->cpt == 2) || (s->bcom->next && s->cpt == 4))
		return (1);
	return (putchar_completion(&*s, &s->bcom, line, c));
}

int		ft_completion(t_struct *s, char **path, char buf[5], int i)
{
	char	*line;
	int		c;

	line = NULL;
	c = 0;
	if (!(path = init_tab_path2(s->env_path)))
		return (-1);
	if (i == 2 && s->lbg && (s->l = s->lbg))
	{
		while (s->l && (c = c + 1))
			s->l = s->l->next;
		s->l = s->lbg;
		if (!(create_line(&line, s, 0, c)))
			return (-1);
		s->com = create_lst_comp(&path, &s->bcom, line, s->l);
		s->bcom = char_class(s->bcom, s->bcom);
		return (1);
	}
	else if (!s->lbg && !s->tmp && buf[0] == 9 && i)
		return (show_commands(&path, 0, NULL, NULL));
	else if (s->lbg && !s->tmp->next && s->cpt > 1)
		return (completion_commands(&path, 0, &*s, 0));
	if (buf[0] == 9)
		return (free_path(&path, 3));
	return (0);
}
