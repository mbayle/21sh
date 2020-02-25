/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 23:39:14 by ymarcill          #+#    #+#             */
/*   Updated: 2020/02/20 00:20:50 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int		list_size(t_lex *lex)
{
	int	i;

	i = 0;
	while (lex && lex->next)
	{
		i += ft_strlen(lex->value);
		lex = lex->next;
	}
	return (i);
}

char	*list_to_string(t_lex *lex)
{
	int		i;
	char	*dst;

	i = 0;
	if (lex == NULL || (dst = ft_strnew(1)) == NULL)
	{
//		ft_putendl("RETURN NULL AVANT DE FILL");
//	if ((dst = malloc(sizeof(char) * (list_size(lex) + 1))) == NULL)
		return (NULL);
	}
//	ft_putstr("Befor the loop: ");
//	ft_putendl(lex->value);
	
//	ft_putstr("NEXT VAL: ");
//	if (!pipe)
//
	while (lex && lex->token != UNKNOWN)
	{
//		ft_putstr("o lex->value in list 2 str: ");
//		ft_putendl(lex->value);
//		if (dst != NULL)
//			ft_putendl("DST XIST");
		dst = ft_strjoinfree(dst, lex->value);
//		ft_putstr("DST : ");
//		ft_putstr(dst);
//		ft_putendl("-");
		if (lex->next)
			dst = ft_strjoinfree(dst, " ");
		lex = lex->next;
	}
	return (dst);
}

void	join_job_line(t_ast *ast, int p_pos)
{
	char	*tmp;
	char	*tmp2;

	
	tmp = ft_strdup(g_jobcontrol.first_job->command);
//	ft_putstr("\ng_joc.. de base tmp = ft_strdup: ");
//	ft_putendl(tmp);
	tmp2 = list_to_string(ast->lex);
//	ft_putstr("\ntmp2 = list_to_string :");
//	ft_putendl(tmp2);
	ft_strdel(&g_jobcontrol.first_job->command);
	if (tmp)
		g_jobcontrol.first_job->command = ft_strjoin(tmp, tmp2);
	else
		g_jobcontrol.first_job->command = ft_strdup(tmp2);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	if (p_pos != 1)
		g_jobcontrol.first_job->command = ft_strjoinfree(g_jobcontrol.first_job->command, " | ");

}

void    check_op_pipe(t_ast *ast, int p_pos)
{
	t_lex   *lex;

	if (ast == NULL)
		return ;
	lex = ast->lex;
	if ((int)lex->operator == 0)
	{
		join_job_line(ast, p_pos);
		if (p_pos == 1)
		{
		//	ft_putstr_fd("TOTAL LINE: ", 2);
		//	ft_putendl_fd(g_jobcontrol.first_job->command, 2);
			do_to_ast();
		}
	}
	/*process aloc in it*/
	/*job->cmd = strjoin in it*/
	/*if p_pos == 1, job->last_ret = actual pro->ret/pro->status*/
	/*check g_jobcontrol.g_fg et set job->fg if appropriate*/
	/*if p_pos == 1, put_in_fgwait all*/
	//	exec_pipeline(ast, p_pos);
	else if ((int)lex->operator == PIPE)
		manage_pipe_bis(ast);
}

void    go_right_pipe(t_ast *ast, int p_pos)
{
	t_ast   *tmp;

	tmp = ast->right;
//	ft_putstr_fd("THE RIGHT: ", 2);
//	ft_putendl_fd(tmp->lex->value, 2);
//	ft_putstr_fd("IN RIGHTPIPE p_pos : ", 2);
//	ft_putnbr_fd(p_pos, 2);
	check_op_pipe(tmp, p_pos);
}

void    go_left_pipe(t_ast *ast, int p_pos)
{
	t_ast   *tmp;

	tmp = ast->left;
//	ft_putstr_fd("IN LEFTPIPE : ", 2);
//	ft_putnbr_fd(p_pos, 2);
	check_op_pipe(tmp, p_pos);
}

void    manage_pipe_bis(t_ast *ast)
{
	int p_pos;

	p_pos = 0;
	if (ast->right && ast->right->lex->operator != 3)
		p_pos = 1;
	go_left_pipe(ast, 0);
	go_right_pipe(ast, p_pos);
	/*
	*/
}
