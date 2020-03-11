/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 02:44:00 by mabayle           #+#    #+#             */
/*   Updated: 2020/01/26 06:16:57 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

/*
** Purpose of the function : Initialize a new node
** Return value : return new node
*/

t_ast	*init_node(t_lex *lex, char *root)
{
	t_ast *new_node;

	if (!(new_node = ft_memalloc(sizeof(t_ast))))
		return (NULL);
	new_node->lex = lex;
	new_node->root = root;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

/*
** Purpose of the function : Loop and set priority (for each lexeme)
** Return value : no return
*/

void	init_priority(t_lex *lex)
{
	if (!lex)
		return ;
	while (lex)
	{
		if (lex->operator == OTHER)
			lex->priority = 0;
		else if (lex->operator == PIPE)
			lex->priority = 1;
		else if (lex->operator == SEMIC || lex->operator == AND)
			lex->priority = 3;
		else if (lex->operator == DAND || lex->operator == DPIPE)
			lex->priority = 2;
		else
			lex->priority = 0;
		lex = lex->next;
	}
}

/*
** Purpose of the function : Special case, input is a simple command
** Return value : return AST (with only root node)
*/

t_ast	*no_root(t_lex *lex, t_ast *ast)
{
	char *new_root;

	new_root = ft_strdup("");
	while (lex && lex->token != UNKNOWN)
	{
		new_root = ft_strjoin(new_root, lex->value);
		new_root = ft_strjoin(new_root, " ");
		lex = lex->next;
	}
	ast->root = new_root;
	return (ast);
}

void	astdel(t_ast **ast)
{
	if (*ast)
	{
		if ((*ast)->left)
			astdel(&(*ast)->left);
		if ((*ast)->right)
			astdel(&(*ast)->right);
		(*ast)->left = NULL;
		(*ast)->right = NULL;
		free(*ast);
		*ast = NULL;
	}
}