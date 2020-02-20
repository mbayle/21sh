/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 01:20:24 by mabayle           #+#    #+#             */
/*   Updated: 2020/02/20 00:22:55 by ymarcill         ###   ########.fr       */
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

/*
** Purpose of the function : Found next priority and call sub_split
** Return value : SUCCESS (or no new priority) = return 1 | else return 0
*/

/*int		find_priority(t_ast *ast, int priority)
{
	t_lex *lex;

	lex = ast->lex;
	if (!ast)
		return (0);
	while (priority >= 1)
	{
		while (lex)
		{
			if (lex->priority == priority)
				if (lex->next != NULL)
					sub_split(ast, lex->pos, priority);
			lex = lex->next;
		}
		priority--;
	}
	return (1);
}*/

/*#include <stdio.h>
void	print_debug(t_ast *ast, int pad)
{
	t_lex *tmp;

	tmp = ast->lex;
	printf("%*s", pad*4, "");
	while (tmp)
	{
		printf("%s (position %d)", tmp->value, tmp->pos);
		tmp = tmp->next;
	}
	printf("\n");
	if (ast->left)
		print_debug(ast->left, pad + 1);
	if (ast->right)
		print_debug(ast->right, pad + 1);
}*/

/*
** Purpose of the function : Calculate depth of my tree and find future
**							priority
** Return value : return depth of my tree
*/

/*int		max_depth(t_ast *ast, int prio)
{
	t_ast	*root;

	root = g_shell->ast;
	if (!ast)
		return (0);
	else
	{
		while (prio >= 1)
		{
			if (ast->left)
			{
				ast = root;
				while (ast->left && ast->left->left)
					ast = ast->left;
				find_priority(ast->left, prio);
			}
			if (ast->right)
			{
				ast = root;
				while (ast->right && ast->right->right)
					ast = ast->right;
				find_priority(ast->right, prio);
			}
			if (!ast->right && !ast->left)
			{
				ast = root;
				find_priority(ast, prio);
			}
			prio--;
		}
	}
	return (0);
}*/

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
		while(priority >= 1)
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

void	do_to_ast()
{
	char	**tmp;

	tmp = quick_tab_cmd(g_jobcontrol.first_job->command);
	ft_putstr("\nJob->command\"[0]\" after quick_tab:");
	ft_putendl(tmp[0]);
	ft_putendl(tmp[1]);
	pipe_exec(tmp, g_jobcontrol.env, g_jobcontrol.g_fg);
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
		ft_putendl("I CREATE THE ASt");
		init_priority(lex);
		*ast = init_node(lex, lex->value);
		*ast = beta_ast(*ast, 3);
		!(*ast)->right && !(*ast)->left ? no_root(lex, (*ast)) : 0;
		browse_ast(*ast);
//		do_to_ast();
		ast && g_shell->debug == 1 ? ft_putast(*ast) : 0;
	}
	return (0);
}
