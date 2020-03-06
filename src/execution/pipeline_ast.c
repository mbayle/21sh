/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 23:39:14 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/06 23:33:50 by ymarcill         ###   ########.fr       */
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
		return (NULL);
	while (lex && lex->token != UNKNOWN)
	{
		if (lex->token == ASSIGN_WORD)
			dst = ft_strjoinfree(dst, "\r");
		dst = ft_strjoinfree(dst, lex->value);
		if (lex->next && lex->token != IO_NUMBER)
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
	tmp2 = list_to_string(ast->lex);
	ft_strdel(&g_jobcontrol.first_job->command);
	if (tmp)
		g_jobcontrol.first_job->command = ft_strjoin(tmp, tmp2);
	else
		g_jobcontrol.first_job->command = ft_strdup(tmp2);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	if (p_pos != 1)
		g_jobcontrol.first_job->command =
			ft_strjoinfree(g_jobcontrol.first_job->command, " | ");
}

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
			do_to_ast();
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
