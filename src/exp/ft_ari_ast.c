/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ari_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 04:44:45 by geargenc          #+#    #+#             */
/*   Updated: 2020/04/14 06:21:29 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

void			ft_ari_ast_insert_parent(t_ari_ast *ast)
{
	t_ari_node	*next;

	next = ast->list->right;
	ast->list->parent = ast->current->parent;
	ast->current->parent = ast->list;
	ast->list->left = ast->current;
	if (ast->list->parent)
		ast->list->parent->right = ast->list;
	else
		ast->begin = ast->list;
	ast->list->right = NULL;
	ast->current = ast->list;
	ast->list = next;
}

void			ft_ari_ast_insert_child(t_ari_ast *ast)
{
	t_ari_node	*next;

	next = ast->list->right;
	if (ast->current)
	{
		ast->current->right = ast->list;
		ast->list->parent = ast->current;
	}
	else
		ast->begin = ast->list;
	ast->list->right = NULL;
	ast->current = ast->list;
	ast->list = next;
}

int				ft_ari_ast(t_ari_ast *ast)
{
	while (ast->list)
	{
		if (g_ari_asttab[ast->list->token].insert(ast))
			return (-1);
	}
	if (ast->current &&
		(g_ari_asttab[ast->current->token].type & ARI_TYPE_OP))
		return (-1); // operande attendu
	while (ast->current)
	{
		if (g_ari_asttab[ast->current->token].type & ARI_TYPE_SUB)
			return (-1); // " ) " manquante
		ast->current = ast->current->parent;
	}
	return (0);
}
