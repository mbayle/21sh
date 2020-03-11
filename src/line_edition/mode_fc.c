/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 00:51:10 by frameton          #+#    #+#             */
/*   Updated: 2020/03/10 00:51:22 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

void	restore_fd_fc(void)
{
	dup2(g_tracking.mysh->dup1, 0);
	close(g_tracking.mysh->dup1);
	dup2(g_tracking.mysh->dup2, 1);
	close(g_tracking.mysh->dup2);
	dup2(g_tracking.mysh->dup3, 2);
	close(g_tracking.mysh->dup3);
}

int		editor_mode(t_fc *f)
{
	if (f->min && f->max == -42)
	{
		f->min = -1;
		f->max = -1;
	}
	if (f->max == -42)
		f->max = f->min;
	if (f->min == -42)
		f->min = f->max;
	create_fc_file(f);
	return (0);
}

int		no_edit_mode(t_fc *f)
{
	if (f->min == -4 && f->max == -42)
		f->max = -1;
	if (f->min == -42 && f->max == -42)
	{
		f->min = -1;
		f->max = -1;
	}
	if (f->min == -1 && f->max == -42)
	{
		f->min = -1;
		f->max = -1;
	}
	create_fc_oldnew(f);
	restore_fd_fc();
	return (0);
}

int		list_mode(t_fc *f)
{
	if (f->min && f->max == -42)
	{
		f->min = -15;
		f->ma = -1;
	}
	if (f->max == -42)
		f->max = -1;
	print_fc(f);
	return (0);
}

int		fc_mode(t_fcparse *opt)
{
	if ((f->e == 1 && f->s == 1) || (f->e == 1 && f->l == 1))
		return (fc_error(3, NULL));
	if ((f->l == 1 && f->s == 1) || (f->l == 1 && f->e == 1))
		return (fc_error(3, NULL));
	if ((f->s == 1 && f->n == 1) || (f->e == 1 && f->n == 1))
		return (fc_error(3, NULL));
	if (f->e == 1)
		return (editor_mode(f));
	if (f->s == 1)
		return (no_edit_mode(f));
	if (f->l == 1)
		return (list_mode(f));
	return (editor_mode(f));
}
