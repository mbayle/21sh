/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:37:37 by frameton          #+#    #+#             */
/*   Updated: 2020/03/10 01:08:35 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

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

void    free_opt(t_fc *f)
{
        if (!opt)
                return ;
        ft_strdel(&opt->editor);
        ft_strdel(&opt->first);
        ft_strdel(&opt->last);
        ft_strdel(&opt->shist);
        ft_strdel(&opt->str);
        ft_free(opt);
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
