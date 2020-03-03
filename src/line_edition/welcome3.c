/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:20:38 by frameton          #+#    #+#             */
/*   Updated: 2020/03/03 22:21:41 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

void	welcome5_b(int m)
{
	ft_putchar('#');
	do_m(m + 8);
	ft_putchar('#');
	fp("up", NULL);
	ft_sleep(0);
}

int		welcome10(int m, t_struct s)
{
	ft_sleep(0);
	ft_putstr("###");
	fp("do", "do");
	do_m(m + 71);
	ft_sleep(0);
	ft_putstr("###");
	es8(m + 70, "###");
	sleep(2);
	tputs(tgetstr("cl", NULL), 1, ft_ptchar);
	tputs(tgetstr("ve", NULL), 1, ft_ptchar);
	print_prompt_bis(s.prompt, &s, 0);
	return (1);
}
