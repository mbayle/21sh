/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:19:29 by ymarcill          #+#    #+#             */
/*   Updated: 2020/02/19 23:52:30 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

void	simple_exec(t_ast *ast)
{
	t_lex	*lex;
	t_lex	*tmp;;

	lex = ast->lex;
	tmp = lex;
	g_jobcontrol.sim = 0;
//	ft_putnbr(g_jobcontrol.g_fg);
	join_job_line(ast, 1);
	do_to_ast();
}
