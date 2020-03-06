/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:19:29 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/06 23:34:30 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

void	simple_exec(t_ast *ast)
{
	t_lex	*lex;
	t_lex	*tmp;

	lex = ast->lex;
	tmp = lex;
	join_job_line(ast, 1);
	do_to_ast();
}
