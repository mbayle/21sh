/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 02:48:35 by ymarcill          #+#    #+#             */
/*   Updated: 2020/02/20 01:22:44 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"
#include "../includes/jobcontrol.h"

void	manage_and(t_ast *ast)
{
	manage_semic(ast, 0);
}

void	manage_dand(t_ast *ast)
{
	go_left(ast);
	if (g_jobcontrol.first_job && g_jobcontrol.first_job->last_ret == 0)
		g_jobcontrol.ret = 0;
	go_right(ast);
}

void	manage_dor(t_ast *ast)
{
	go_left(ast);
	if (g_jobcontrol.first_job && g_jobcontrol.first_job->last_ret == 0)
		g_jobcontrol.ret = -1;
	go_right(ast);
}

void	check_op(t_ast *ast)
{
	t_ast *tmp;
	t_lex	*lex;

	tmp = ast;
	lex = ast->lex;
	if (tmp == NULL || lex == NULL || lex->token == UNKNOWN)
		return ;
	if ((int)lex->operator == 0)
		manage_word(ast);
	if ((int)lex->operator == 1)
		manage_semic(ast, 1);
	else if ((int)lex->operator == 3)
		manage_pipe(ast);
	else if ((int)lex->operator == 4)
		manage_dor(ast);
	else if ((int)lex->operator == 5)
		manage_and(ast);
	else if ((int)lex->operator == 6)
		manage_dand(ast);
}

void	browse_ast(t_ast *ast)
{
	g_jobcontrol.g_fg = 1;
	check_op(ast);
}

