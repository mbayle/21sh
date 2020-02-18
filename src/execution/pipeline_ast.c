/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 23:39:14 by ymarcill          #+#    #+#             */
/*   Updated: 2020/02/18 02:27:26 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		list_size(t_lex *lex)
{
	int	i;

	i = 0;
	while (lex)
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
	if ((dst = ft_strnew(1)) == NULL)
//	if ((dst = malloc(sizeof(char) * (list_size(lex) + 1))) == NULL)
		return (NULL);
	while (lex)
	{
		dst = ft_strjoinfree(dst, lex->value);
		if (lex->next);
			dst = ft_strjoinfree(dst, " ");
		lex = lex->next;
	}
}

void	join_job_line(t_ast *ast, int p_pos)
{
	char	*tmp;
	char	*tmp2;
	t_lex	*lex;

	
	tmp = ft_strdup(g_jobcontrol.first_job->command);
	tmp2 = list_to_string(at->lex);
	ft_strdel(&g_jobcontrol.first_job->command);

	g_jobcontrol.first_job->command = ft_strjoin(tmp, tmp2);
	ft_strdel(&tmp);
	ft_strdel(&tmp);
	if (p_pos)
		g_jobcontrol.first_job->command = ft_strjoinfree(g_jobcontrol.first_job->comand, " | ");

}

void    check_op_pipe(t_ast *ast, int p_pos)
{
	t_lex   *lex;

	if (tmp == NULL)
		return ;
	lex = ast->lex;
	if ((int)lex->operator == 0)
	{
		join_job_line(ast, p_pos);
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
	check_op_pipe(tmp);
}

void    go_left_pipe(t_ast *ast, int p_pos)
{
	t_ast   *tmp;

	tmp = ast->left;
	check_op_pipe(tmp);
}

void    manage_pipe_bis(t_ast *ast)
{
	int p_pos;

	p_pos = 0;
	if (ast->right && ast->right->lex->operator != 3)
		p_pos = 1;
	go_left_pipe(ast, p_pos);
	go_right_pipe(ast, p_pos);
	/*
	*/
}
