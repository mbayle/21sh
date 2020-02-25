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

void	manage_and(t_ast *ast)
{
	manage_semic(ast, 0);
}

void	manage_dand(t_ast *ast)
{
	go_left(ast);
	if (g_jobcontrol.first_job && g_jobcontrol.first_job->last_ret == 0)
		go_right(ast);
}

void	manage_dor(t_ast *ast)
{
	go_left(ast);
	if (g_jobcontrol.first_job && g_jobcontrol.first_job->last_ret != 0)
		go_right(ast);
}

void	manage_pipe(t_ast *ast)
{
	int p_pos;

	allocate_job_loop(0);
//	ft_putendl("I have a pipe");
/*	joballocation : (next ? ..)
	job->cmd = ft_strdup(ast->left->lex->value..)
	free(tmp);*/
	p_pos = 0;
	if (ast->right && ast->right->lex->operator != 3)
		p_pos = 1;	
	go_left_pipe(ast, 0);
	go_right_pipe(ast, p_pos);
}



void	check_op(t_ast *ast)
{
	t_ast *tmp;
	t_lex	*lex;

	tmp = ast;
	lex = ast->lex;
	ft_putstr("In check op ma val is : ");
	ft_putendl(lex->value);
	if (tmp == NULL || lex == NULL || lex->token == UNKNOWN)
		return ;
	if ((int)lex->operator == 0)
	/*job allocation in it*/
	/*check g_jobcontrol.g_fg et set job->fg if appropriate*/
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







/*void	check_op_pipe(t_ast *ast, int p_pos)
{
	t_lex	*lex;

	if (tmp == NULL)
		return ;
	lex = ast->lex;
	if ((int)lex->operator == 0)
	//process aloc in it
	//job->cmd = strjoin in it
		exec_pipeline(ast, p_pos);
	else if ((int)lex->operator == PIPE)
		manage_pipe_bis(ast);
}

void	go_right_pipe(t_ast *ast, int p_pos)
{
	t_ast	*tmp;

	tmp = ast->right;
	check_op_pipe(tmp);
}

void	go_left_pipe(t_ast *ast, int p_pos)
{
	t_ast	*tmp;

	tmp = ast->left;
	check_op_pipe(tmp);
}

void	manage_pipe_bis(t_ast *ast)
{
	int p_pos;

	p_pos = 0;
	if (ast->right && ast->right->lex->operator != 3)
		p_pos = 1;
	go_left_pipe(ast, p_pos);
	go_right_pipe(ast, p_pos);

}*/

