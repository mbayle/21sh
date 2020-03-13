/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:19:29 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/12 22:31:39 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

void	simple_exec(t_ast *ast)
{
	t_lex	*lex;
	t_lex	*tmp;
	int		y;

	y = 0;
	lex = ast->lex;
	tmp = lex;
	while (g_jobcontrol.arg && g_jobcontrol.arg[y] && y <= g_jobcontrol.index)
	{
		ft_freetab(g_jobcontrol.arg[y]);
		y++;
	}
	g_jobcontrol.index = 0;
	if (!(g_jobcontrol.arg = malloc(sizeof(char**) * 4097)))
		return ;
	join_job_line(ast, 1);
	do_to_ast(g_jobcontrol.arg);
}
