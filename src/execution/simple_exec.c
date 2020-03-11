/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:19:29 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/11 05:22:45 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

void	simple_exec(t_ast *ast)
{
	t_lex	*lex;
	t_lex	*tmp;
	int		y;
//	char	***cmd;

	y = 0;
	lex = ast->lex;
	tmp = lex;
//	ft_putendl("SIM PLE");
//	while (g_jobcontrol.arg && g_jobcontrol.arg[y])
//		ft_printtab(g_jobcontrol.arg[y++]);
	y = 0;	
	while (g_jobcontrol.arg && g_jobcontrol.arg[y] && y <= g_jobcontrol.index)
	{
//		printf("%s %p\n", g_jobcontrol.arg[y][0], g_jobcontrol.arg[y][0]);
//		printf("\n%s %p\n", "g_jobcontrol.arg[y]", g_jobcontrol.arg[y]);
		ft_freetab(g_jobcontrol.arg[y]);
		y++;
	}
//	ft_memdel((void**)g_jobcontrol.arg);
	g_jobcontrol.index = 0;
	if (!(g_jobcontrol.arg = malloc(sizeof(char**) * 4097)))
 	  	return ;
//	ft_putendl("\nAFTER ALLOC BEFORE JOIN SIMPLE");
  	join_job_line(ast, 1);
//	g_jobcontrol.arg[g_jobcontrol.index] = NULL;
	do_to_ast(g_jobcontrol.arg);
}
