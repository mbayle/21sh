/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:37:37 by frameton          #+#    #+#             */
/*   Updated: 2020/03/09 20:20:04 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int                     fc_error(int i, char *str)
{
	if (i == 1)
		ft_putendl_fd("Too many arguments", 2);
	if (i == 2)
		ft_putendl_fd("Invalid option", 2);
	if (i == 3)
		ft_putendl_fd("Incompatible option", 2);
	if (i == 4)
	{
		ft_putstr_fd("Argument out of history range :", 2);
		ft_putendl_fd(str, 2);
		return (-42);
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

int		exec_fc(t_struct *s)
{
	t_fc	f;
	int		i;
	char	**av;

	i = 1;
	if ((av = ft_splitws(s->cmd)) == NULL)
		return (1);
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
}
