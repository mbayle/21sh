/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:37:37 by frameton          #+#    #+#             */
/*   Updated: 2020/03/09 23:43:35 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		 parse_error(int i, char *str)
{
	if (i == 1)
		ft_eputendl("fc: error: too many arguments");
	if (i == 2)
		ft_eputendl("fc: error: invalid option");
	if (i == 3)
		ft_eputendl("fc: error: incompatible option");
	if (i == 4)
	{
		ft_eputstr("Argument out of history range :");
		ft_eputendl(str);
		return (0);
	}
	return (1);
}

int		init_struct_fc(t_fc *f)
{
	f->e = 0;
	f->err = 0;
	f->i = 0;
	f->s = 0;
	f->r = 0;
	f->n = 0;
	f->l = 0;
	f->min = 0;
	f->max = 0;
	f->edtr = NULL;
	f->opt = NULL;
}

void	init_opt(t_fc *f , char **s)
{
	char	*tmp;

	tmp = *s;
	tmp++;
	f->opt = tmp;
}

void	parse_opt(t_fc *f)
{
	int		i;
	char	c;

	i = 0;
	while (f->opt && f->opt[i])
	{
		c = f->opt[i];
		if (c == 'l')
			f->l = 1;
		if (c == 'e')
			f->e = 1;
		if (c == 's')
			f->s = 1;
		if (c == 'n')
			f->n = 1;
		if (c == 'r')
			f->r = 1;
		if (c != 'l' && c != 'r' && c != 'n' && c != 'e' && c != 's')
			f->ret = 1;
		++i;
	}
}

int		check_f(char **av, t_fc *f)
{
	int		i;

	i = (*f)->i;
	if (!av)
		return (0);
	if (av[i])
	{
		(*f)->frst = ft_strdup(av[i]);
		++i;
	}
	if (av[i])
	{
		(*f)->scd = ft_strdup(av[i]);
		++i;
	}
	if (av[i])
	{
		parse_error(1, NULL);
		return (0);
	}
	return (1);
}

void	rev_list(t_fc *f)
{
	int		tmp;

	tmp = f->min;
	f->min = f->max;
	f->max = tmp;
	tmp = f->r;
	if (tmp == 1)
		f->r = 0;
	if (tmp == 0)
		f->r = 1;
}

int		digit_or_str(char *str)
{
	int i;

	i = 0;
	if (str)
	{
		if (ft_isdigit(str[i]) == 1)
			return (0);
		if (str[i] == '+' || str[i] == '-')
		{
			i++;
			if (ft_isdigit(str[i]) == 1)
				return (0);
		}
	}
	return (1);
}

int		fc_get_index(char *str)
{
	t_list		*history;
	char		*buf;
	int			i;

	if (!g_tracking.mysh->hist)
		return (fc_error(4, str));
	if (!str || eq_sign(str) > 0)
		return (-42);
	history = ft_lstgetlast(g_tracking.mysh->hist->firstelement);
	if (!history)
		return (fc_error(4, str));
	i = ft_strlen(str);
	while (history)
	{
		buf = history->content;
		if (ft_strncmp(str, buf, i) == 0)
			return (history->index);
		history = history->prev;
	}
	return (fc_error(4, str));
}

void	char_to_index(t_fc *f)
{
	int		tmp;

	tmp = 0;
	if (digit_or_str(f->frst) == 0)
		f->min = ft_atoi(f->frst);
	else
	{
		if (eq_sign(f->frst) == 1)
		{
			if (f->s != 1)
				parse_error(5, NULL);
			else
				f->min = -4;
		}
		else
			f->min = fc_get_index(f->frst);
	}
	if (digit_or_str(f->scd) == 0)
		f->max = ft_atoi(f->scd);
	else
		f->max = fc_get_index(f->scd);
	if (f->min > f->max && f->s != 1)
		rev_list(f);
}

void	restore_fd_fc(void)
{
	dup2(g_tracking.mysh->dup1, 0);
	close(g_tracking.mysh->dup1);
	dup2(g_tracking.mysh->dup2, 1);
	close(g_tracking.mysh->dup2);
	dup2(g_tracking.mysh->dup3, 2);
	close(g_tracking.mysh->dup3);
}

int		editor_mode(t_fc *f)
{
	if (f->min && f->max == -42)
	{
		f->min = -1;
		f->max = -1;
	}
	if (f->max == -42)
		f->max = f->min;
	if (f->min == -42)
		f->min = f->max;
	create_fc_file(f);
	return (0);
}

int		no_edit_mode(t_fc *f)
{
	if (f->min == -4 && f->max == -42)
		f->max = -1;
	if (f->min == -42 && f->max == -42)
	{
		f->min = -1;
		f->max = -1;
	}
	if (f->min == -1 && f->max == -42)
	{
		f->min = -1;
		f->max = -1;
	}
	create_fc_oldnew(f);
	restore_fd_fc();
	return (0);
}

int		list_mode(t_fc *f)
{
	if (f->min && f->max == -42)
	{
		f->min = -15;
		f->ma = -1;
	}
	if (f->max == -42)
		f->max = -1;
	print_fc(f);
	return (0);
}

int		fc_mode(t_fcparse *opt)
{
	if ((f->e == 1 && f->s == 1) || (f->e == 1 && f->l == 1))
		return (fc_error(3, NULL));
	if ((f->l == 1 && f->s == 1) || (f->l == 1 && f->e == 1))
		return (fc_error(3, NULL));
	if ((f->s == 1 && f->n == 1) || (f->e == 1 && f->n == 1))
		return (fc_error(3, NULL));
	if (f->e == 1)
		return (editor_mode(f));
	if (f->s == 1)
		return (no_edit_mode(f));
	if (f->l == 1)
		return (list_mode(f));
	return (editor_mode(f));
}

int		exec_fc(t_struct *s, char **av)
{
	t_fc	f;
	int		i;
	int		ac;
	char	**av;

	i = 1;
	ac = 0;
	init_struct_fc(&f);
	while (av[i] && ft_strcmp(av[i], "--") != 0 && ft_isinteg(av[i]) != 0)
	{
		if (ft_strcmp(av[i - 1], "-e") == 0)
			f->edtr = ft_mstrcpy(av[i]);
		else
		{
			if (av[i][0] != '-')
				break ;
			init_opt(&f, &av[i]);
		}
		++i;
	}
	if (!ft_strcmp(av[i], "--"))
		i++;
	f->i = i;
	if (opt->str)
		opt = parse_opt(&f);
	f->h = s->h;
	while (av[ac])
		++ac;
	if (ac == 1 || !(check_f(av, &f)))
		return (1);
	if (f->ret)
		parse_error(2, NULL);
	char_to_index(&f);
	fc_mode(&f);
	return (0);
}
