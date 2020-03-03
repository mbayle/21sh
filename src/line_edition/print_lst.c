/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:24:43 by frameton          #+#    #+#             */
/*   Updated: 2020/03/03 22:09:01 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

static t_lst	*print_lst2(t_struct s, int *c, int *i, int *nl)
{
	s.l = s.lbg;
	while (s.l)
	{
		if (s.l->sel)
			ft_putstr(BWHITE);
		if (s.eq || s.edq)
			fp("bl", NULL);
		if (s.eq && s.l->c == '\'')
			ft_putstr(RED);
		if (s.edq && s.l->c == '"')
			ft_putstr(RED);
		write(1, &s.l->c, 1);
		ft_putstr(WHITE);
		*c = s.l->plc;
		if (s.l->plc == *i)
		{
			ft_putchar('\n');
			(*nl)++;
			*i = *i + s.col;
		}
		s.l = s.l->next;
	}
	return (s.l);
}

void			write_lst3(int *c, t_struct s, int *i, int *nl)
{
	char	*save;

	save = s.comp.name;
	while (save && s.comp.sz--)
	{
		(*c)++;
		if (*c == *i)
		{
			ft_putchar('\n');
			(*nl)++;
			*i = *i + s.col;
		}
		ft_putstr(BCYAN);
		ft_putchar(*save++);
		ft_putstr(WHITE);
	}
}

int				print_lst(t_struct s, int *nl, int c)
{
	int		i;

	i = s.col;
	*nl = 0;
	tputs(tgetstr("dl", NULL), 1, ft_ptchar);
	s.cki = check_input_exist(s, s.bcom);
	if (s.cki && s.cpt > 1)
		print_prompt_bis(s.prompt, &s, 1);
	else
		print_prompt_bis(s.prompt, &s, 0);
	s.l = print_lst2(s, &c, &i, &*nl);
	write_lst3(&c, s, &i, &*nl);
	return (s.cki);
}
