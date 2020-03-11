/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 23:29:07 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/11 05:26:47 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

void	manage_word(t_ast *ast)
{
	allocate_job_loop(0);
	simple_exec(ast);
}

void	go_left(t_ast *ast)
{
	t_ast	*tmp;

	tmp = ast->left;
	check_op(tmp);
}

void	go_right(t_ast *ast)
{
	t_ast	*tmp;

	tmp = ast->right;
	check_op(tmp);
}

void	manage_semic(t_ast *ast, int fg)
{
	if (fg == 0)
		g_jobcontrol.g_fg = 0;
	go_left(ast);
	g_jobcontrol.g_fg = 1;
	go_right(ast);
}

void	manage_pipe(t_ast *ast)
{
	int	p_pos;
	int	y;

	y = 0;
	while (g_jobcontrol.arg && g_jobcontrol.arg[y] && y < g_jobcontrol.index)
	{
//		printf("%s %p\n", "av ", g_jobcontrol.arg);
//		printf("%s %p\n", "av[i] ", g_jobcontrol.arg[y]);
		ft_freetab(g_jobcontrol.arg[y]);
		y++;
	}
	g_jobcontrol.index = 0;
	if (!(g_jobcontrol.arg = malloc(sizeof(char**) * 4097)))
		return ;
	g_jobcontrol.sim = 1;
	allocate_job_loop(0);
	p_pos = 0;
	if (ast->right && ast->right->lex->operator != 3)
		p_pos = 1;
	go_left_pipe(ast, 0);
	go_right_pipe(ast, p_pos);
}
