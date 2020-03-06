/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_comp_tab5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 23:43:30 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 02:16:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int		other_touch(char buf[5], int *j, t_struct *s)
{
	int		c;

	c = 0;
	while (c < *j + 1)
	{
		fp("up", "dl");
		++c;
	}
	if (buf[0] == 127 || (buf[0] == 27 && buf[3] == 126))
		del_move(2);
	else
		del_move(1);
	*j = 0;
	print_prompt_bis(s->prompt, &*s, 0);
	s->l = s->lbg;
	while (s->l)
	{
		ft_putchar(s->l->c);
		s->l = s->l->next;
	}
	s->l = s->lbg;
	fp("ve", NULL);
	return (1);
}
