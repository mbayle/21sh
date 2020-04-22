/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clr_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:24:57 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 22:33:19 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

static void	clr_shell2(int i)
{
	if (i == 8)
		ft_putstr(MAGENTA);
	if (i == 9)
		ft_putstr(FMAGENTA);
	if (i == 10)
		ft_putstr(CYAN);
	if (i == 11)
		ft_putstr(FCYAN);
	if (i == 12)
		ft_putstr(WHITE);
	if (i == 13)
		ft_putstr(GREY);
}

void		clr_shell(int i)
{
	if (!i)
		ft_putstr(BLUE);
	if (i == 1)
		ft_putstr(FBLUE);
	if (i == 2)
		ft_putstr(RED);
	if (i == 3)
		ft_putstr(FRED);
	if (i == 4)
		ft_putstr(GREEN);
	if (i == 5)
		ft_putstr(FGREEN);
	if (i == 6)
		ft_putstr(YELLOW);
	if (i == 7)
		ft_putstr(FYELLOW);
	clr_shell2(i);
}
