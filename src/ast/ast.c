/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 01:20:24 by mabayle           #+#    #+#             */
/*   Updated: 2020/02/05 00:45:42 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

/*
** Purpose of the function : Find next priority and split my tree
** Return value : return ast
*/

t_ast	*sub_split(t_ast *ast, int find, int priority)
{
	t_lex *left;
	t_lex *current;
	t_lex *right;

	left = NULL;
	current = ast->lex;
	right = NULL;
	while (current->pos <= find)
	{
		left = current;
		if (current->next->priority == priority)
		{
			right = current->next;
			break ;
		}
		current = current->next;
	}
	(current->next) && ft_strcmp(ast->root, g_shell->lex->value) == 0
			? ast->root = current->next->value : 0;
	if (right)
	{
		right = split_lex3(ast->lex, current->next->pos);
		ast->right = init_node(right, "NULL");
		left = split_lex2(ast->lex, left->pos);
		ast->left = init_node(left, "NULL");
		find_priority(ast->right, priority);
	}
	if (left)
		find_priority(ast->left, priority);
	return (ast);
}

/*
** Purpose of the function : Found next priority and call sub_split
** Return value : SUCCESS (or no new priority) = return 1 | else return 0
*/

int		find_priority(t_ast *ast, int priority)
{
	t_lex *lex;

	lex = ast->lex;
	if (!ast)
		return (0);
	else
	{
		while (lex)
		{
			if (lex->priority == priority)
				if (lex->next != NULL)
					sub_split(ast, lex->pos, priority);
			lex = lex->next;
		}
	}
	return (1);
}

/*
** Purpose of the function : Calculate depth of my tree and find future
**							priority
** Return value : return depth of my tree
*/

int		max_depth(t_ast *ast, int prio)
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
			else
			{
				ast = root;
				find_priority(ast, prio);
			}
			prio--;
		}
	}
	return (0);
}

/*
** Purpose of the function : Create my AST
** Steps  : 1 - Get priority for all token
**			2 - Init root node and build AST with max priority
**			3 - Split my tree with other priority
**			4 - Special case = edit value for root node
**			5 - If debug active -> print AST
** Return value : return ast
*/

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
		*ast = create_ast(*ast, 3);
		depth_max = max_depth((*ast), 2);
		!(*ast)->right && !(*ast)->left ? no_root(lex, (*ast)) : 0;
		ast && g_shell->debug == 1 ? ft_putast(*ast) : 0;
	}
	return (0);
}
