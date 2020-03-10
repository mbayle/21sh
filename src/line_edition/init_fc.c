/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 00:56:30 by frameton          #+#    #+#             */
/*   Updated: 2020/03/10 00:56:34 by frameton         ###   ########.fr       */
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
