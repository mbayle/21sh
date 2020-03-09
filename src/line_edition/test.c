/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 23:21:24 by frameton          #+#    #+#             */
/*   Updated: 2020/03/09 02:24:03 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int		ft_test2(char **av, int ac, int c, int c2)
{
	if (ac != 4)
		return (1);
	while (av[1][c] && ft_strcmp(av[2], "=") && ft_strcmp(av[2], "!="))
	{
		if ((c > 0 && av[1][c] == '-') || (av[1][c] != '-'
					&& !ft_isnum(av[1][c])))
		{
			ft_2eputstr("test: ", av[1]);
			ft_eputendl(": integer expression expected");
			return (1);
		}
		++c;
	}
	while (av[3][c2] && ft_strcmp(av[2], "=") && ft_strcmp(av[2], "!="))
	{
		if ((c2 > 0 && av[3][c2] == '-') || (av[1][c2] != '-'
					&& !ft_isnum(av[3][c2])))
		{
			ft_2eputstr("test: ", av[3]);
			ft_eputendl(": integer expression expected");
			return (1);
		}
		++c2;
	}
	return (check_op_4(av, ft_atoi(av[1]), ft_atoi(av[3])));
}

int		ft_test(char **av, int ac, char *p)
{
	t_struct2	st;
	struct stat	s;

	puts("9");
	while (av[ac])
		++ac;
	if (ac > 4)
		ft_eputendl("test: too many arguments");
	if (ac == 3 || ac == 2)
	{
		if (ac == 3 && (set_p_ac(&p, av[2], &st)) == -1)
			return (1);
		if (ac == 2 && (!ft_strcmp(av[1], "!") || !ft_strcmp(av[1], "-z")))
			return (0);
		if (ac == 3 && !ft_strcmp(av[1], "!"))
			return (1);
		if (ac == 2 && (set_p_ac(&p, av[1], &st)) == -1)
			return (1);
		if ((lstat(p, &s)) == -1)
			return (1);
		set_s(&st, s, &p);
		if (ac == 3 && (st.av = av[1]))
			return (check_op_3(&st));
	}
	return (ft_test2(av, ac, 0, 0));
}
