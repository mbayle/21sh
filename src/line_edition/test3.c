/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 02:47:14 by frameton          #+#    #+#             */
/*   Updated: 2020/03/03 22:09:01 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

static int	check_op_3_b4(t_struct2 *st)
{
	ft_eputstr("test: unknown condition: ");
	ft_eputendl(st->av);
	return (1);
}

static int	check_op_3_b3(t_struct2 *st)
{
	if (!ft_strcmp(st->av, "-u"))
	{
		if (st->suid)
			return (0);
		return (1);
	}
	if (!ft_strcmp(st->av, "-w"))
	{
		if (st->wrt)
			return (0);
		return (1);
	}
	if (!ft_strcmp(st->av, "-x"))
	{
		if (st->exc)
			return (0);
		return (1);
	}
	if (!ft_strcmp(st->av, "-z"))
	{
		if (ft_strlen(st->name))
			return (0);
		return (1);
	}
	return (check_op_3_b4(st));
}

static int	check_op_3_b2(t_struct2 *st)
{
	if (!ft_strcmp(st->av, "-p"))
	{
		if (st->fifo)
			return (0);
		return (1);
	}
	if (!ft_strcmp(st->av, "-r"))
	{
		if (st->rd)
			return (0);
		return (1);
	}
	if (!ft_strcmp(st->av, "-S"))
	{
		if (st->sock)
			return (0);
		return (1);
	}
	if (!ft_strcmp(st->av, "-s"))
	{
		if (st->sz)
			return (0);
		return (1);
	}
	return (check_op_3_b3(st));
}

static int	check_op_3_b(t_struct2 *st)
{
	if (!ft_strcmp(st->av, "-e"))
		return (0);
	if (!ft_strcmp(st->av, "-f"))
	{
		if (st->reg)
			return (0);
		return (1);
	}
	if (!ft_strcmp(st->av, "-g"))
	{
		if (st->sgid)
			return (0);
		return (1);
	}
	if (!ft_strcmp(st->av, "-L"))
	{
		if (st->lnk)
			return (0);
		return (1);
	}
	return (check_op_3_b2(st));
}

int			check_op_3(t_struct2 *st)
{
	if (ft_strlen(st->av) != 2 && ft_strcmp(st->av, "!"))
	{
		ft_eputstr("test: error condition : ");
		ft_eputendl(st->av);
		return (1);
	}
	if (!ft_strcmp(st->av, "-b"))
	{
		if (st->blk)
			return (0);
		return (1);
	}
	if (!ft_strcmp(st->av, "-c"))
	{
		if (st->chr)
			return (0);
		return (1);
	}
	if (!ft_strcmp(st->av, "-d"))
	{
		if (st->dir)
			return (0);
		return (1);
	}
	return (check_op_3_b(st));
}
