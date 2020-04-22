/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setclr3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 23:01:08 by frameton          #+#    #+#             */
/*   Updated: 2020/03/10 02:52:38 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

void	anim_cpt2(int *lr, int *s, int m)
{
	while ((*lr)--)
		tputs(tgetstr("do", NULL), 1, ft_ptchar);
	*lr = *s;
	*s = m + 42;
	while ((*s)--)
		tputs(tgetstr("nd", NULL), 1, ft_ptchar);
	*s = *lr;
	tputs(tgetstr("sc", NULL), 1, ft_ptchar);
}
