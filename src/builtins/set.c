/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 14:43:56 by ymarcill          #+#    #+#             */
/*   Updated: 2020/04/22 14:43:57 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		myset(char **cmd)
{
	t_myloc	*loc;

	loc = g_jobcontrol.myloc;
	if (cmd[1])
		return (0);
	while (loc)
	{
		ft_putendl(loc->keyval);
		loc = loc->next;
	}
	return (0);
}
