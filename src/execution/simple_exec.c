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
//	while (lex)
//	{
//		ft_putstr("lex->value simple_exec: ");
//		ft_putendl(lex->value);
//		ft_putstr("\nAST_>lex->value simple_exec: ");
//		ft_putendl(ast->lex->value);
//		lex = lex->next;
//	}
	join_job_line(ast, 1);
//	ft_putstr("\njob command after created: ");
//	ft_putendl(g_jobcontrol.first_job->command);
	do_to_ast();
}
