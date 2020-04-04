/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 01:20:24 by mabayle           #+#    #+#             */
/*   Updated: 2020/03/25 00:53:20 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

/*
** Purpose of the function : Find next priority and split my tree
** Return value : return ast
*/

void	sub_split(t_ast *ast, int priority)
{
	t_lex	*left;
	t_lex	*current;
	t_lex	*right;

	left = NULL;
	current = NULL;
	right = ast->lex;
	if (!right || (right && !right->next))
		return ;
	while (right && right->next)
	{
		if (right->next->priority == priority)
		{
			current = right->next;
			left = right;
			break ;
		}
		right = right->next;
	}
	ast->right = init_node(current->next, NULL);
	current ? current->next = NULL : 0;
	left ? left->next = NULL : 0;
	ast->left = init_node(ast->lex, NULL);
	ast->lex = current;
}

int		is_in_lexer(t_lex *lex, int priority)
{
	if (!lex)
		return (-1);
	while (lex)
	{
		if (lex->priority == priority)
			return (1);
		lex = lex->next;
	}
	return (0);
}

t_ast	*beta_ast(t_ast *ast, int priority)
{
	if (!ast)
		return (NULL);
	if (ast)
	{
		while (priority >= 1)
		{
			if (is_in_lexer(ast->lex, priority))
				sub_split(ast, priority);
			if (ast->right)
				beta_ast(ast->right, priority);
			if (ast->left)
				beta_ast(ast->left, priority);
			priority--;
		}
	}
	return (ast);
}

/*
** Purpose of the function : Create my AST
** Steps  : 1 - Get priority for all token
**			2 - Init root current and build AST with max priority
**			3 - Split my tree with other priority
**			4 - Special case = edit value for root current
**			5 - If debug active -> print AST
** Return value : return ast
*/

void	do_to_ast(char ***tmp)
{
//	char	**tmp;
//(void)tmp;
//	tmp = quick_tab_cmd(g_jobcontrol.first_job->command);
	pipe_exec(tmp, g_jobcontrol.g_fg);
}

int		build_ast(t_lex *lex, t_ast **ast)
{
	int depth_max;

	depth_max = 0;
	if (!ast)
		return (-1);
	*ast = NULL;
	if (lex && lex->token != UNKNOWN)
	{
		init_priority(lex);
		*ast = init_node(lex, lex->value);
		*ast = beta_ast(*ast, 3);
		browse_ast(*ast);
		ast && g_shell->debug == 1 ? ft_putast(*ast) : 0;
		astdel(ast);
		g_shell->lex = NULL;
	}
	return (0);
}
