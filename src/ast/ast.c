/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 01:20:24 by mabayle           #+#    #+#             */
/*   Updated: 2020/01/20 03:06:31 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

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
	if (right)
	{
		right = split_lex3(ast->lex, current->next->pos);
		ast->right = init_node(right, "NULL");
		left = split_lex2(ast->lex, left->pos);
		ast->left = init_node(left, "NULL");
	}
	return (ast);
}

t_ast	*browse_ast(t_ast *ast, int find, int priority)
{
	if ((ast->right || ast->left) && ast->lex->pos < find)
	{
		if (ast->lex->pos > find)
			browse_ast(ast->right, find, priority);
		if (ast->lex->pos < find)
			browse_ast(ast->left, find, priority);
	}
	else
		ast = sub_split(ast, find, priority);
	return (ast);
}

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

int		max_depth(t_ast *ast, int left_depth, int right_depth)
{
	int priority;

	priority = 2;
	if (!ast)
		return (0);
	else
	{
		while (priority >= 1)
		{
			if (ast->left)
				find_priority(ast->left, priority);
			if (ast->right)
				find_priority(ast->right, priority);
			priority--;
		}
		left_depth = max_depth(ast->left, left_depth, right_depth);
		right_depth = max_depth(ast->right, left_depth, right_depth);
		if (left_depth > right_depth)
			return (left_depth + 1);
		else
			return (right_depth + 1);
	}
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
		*ast = create_ast(*ast, 3);
		depth_max = max_depth((*ast), 2, 2);
		!(*ast)->right && !(*ast)->left ? no_root(lex, (*ast)) : 0;
		ast && g_shell->debug == 1 ? ft_putast(*ast) : 0;
	}
	return (0);
}
