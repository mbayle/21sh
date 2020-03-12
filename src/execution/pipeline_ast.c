/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 23:39:14 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/12 02:12:12 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

void	check_op_pipe(t_ast *ast, int p_pos)
{
	t_lex	*lex;

	if (ast == NULL)
		return ;
	lex = ast->lex;
	if ((int)lex->operator == 0)
	{
		join_job_line(ast, p_pos);
		if (p_pos == 1)
		{
			g_jobcontrol.arg[g_jobcontrol.index] = NULL;
			do_to_ast(g_jobcontrol.arg);
		}
	}
	else if ((int)lex->operator == PIPE)
		manage_pipe_bis(ast);
}

void	go_right_pipe(t_ast *ast, int p_pos)
{
	t_ast	*tmp;

	tmp = ast->right;
	check_op_pipe(tmp, p_pos);
}

void	go_left_pipe(t_ast *ast, int p_pos)
{
	t_ast	*tmp;

	tmp = ast->left;
	check_op_pipe(tmp, p_pos);
}

void	manage_pipe_bis(t_ast *ast)
{
	int p_pos;

	p_pos = 0;
	if (ast->right && ast->right->lex->operator != 3)
		p_pos = 1;
	go_left_pipe(ast, 0);
	go_right_pipe(ast, p_pos);
}
