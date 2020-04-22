/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 23:01:08 by frameton          #+#    #+#             */
/*   Updated: 2020/03/10 02:52:38 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

void		outil_copy_history(t_htr **t, t_struct *s, int c)
{
	if (!*t)
		*t = s->h;
	else if (*t && (*t)->next && c == 65)
		*t = (*t)->next;
	else if (*t && (*t)->prev && c == 66)
		*t = (*t)->prev;
}

void		error_exit(char *err)
{
	g_jobcontrol.ret = 1;
	ft_putendl_fd(err, 2);
}
