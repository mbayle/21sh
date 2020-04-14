/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ari_ast_operators.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 04:40:53 by geargenc          #+#    #+#             */
/*   Updated: 2020/04/14 06:21:29 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int				ft_ari_ast_ps(t_ari_ast *ast)
{
	t_ari_node	*next;

	if (!ast->current ||
		(g_ari_asttab[ast->current->token].type & ARI_TYPE_OP))
	{
		next = ast->list->right;
		free(ast->list);
		ast->list = next;
	}
	else
		return (ft_ari_ast_op(ast));
	return (0);
}

int				ft_ari_ast_ms(t_ari_ast *ast)
{
	if (!ast->current ||
		(g_ari_asttab[ast->current->token].type & ARI_TYPE_OP))
	{
		ast->list->token = ARI_MS_SIGN;
		ft_ari_ast_insert_child(ast);
	}
	else
		return (ft_ari_ast_op(ast));
	return (0);
}

int				ft_ari_ast_op(t_ari_ast *ast)
{
	if (!ast->current ||
		!(g_ari_asttab[ast->current->token].type & ARI_TYPE_VALUE))
		return (-1); // erreur syntaxe
	if (ast->current)
		while (ast->current->parent &&
			g_ari_asttab[ast->current->parent->token].priority >=
			g_ari_asttab[ast->list->token].priority)
			ast->current = ast->current->parent;
	ft_ari_ast_insert_parent(ast);
	return (0);
}

int				ft_ari_ast_as(t_ari_ast *ast)
{
	if (!ast->current ||
		!(g_ari_asttab[ast->current->token].type & ARI_TYPE_VAR) ||
		(ast->current->parent &&
		!(g_ari_asttab[ast->current->parent->token].type & ARI_TYPE_SUB)))
		return (-1); // affectation à une non variable
	ft_ari_ast_insert_parent(ast);
	return (0);
}

int				ft_ari_ast_db(t_ari_ast *ast)
{
	if (ast->current &&
		(g_ari_asttab[ast->current->token].type & ARI_TYPE_VAR))
	{
		if (ast->current->parent &&
			(g_ari_asttab[ast->current->parent->token].type & ARI_TYPE_DB))
			return (-1); // double symbole ++/--
		ft_ari_ast_insert_parent(ast);
		ast->current = ast->current->left;
	}
	else
		ft_ari_ast_insert_child(ast);
	return (0);
	
}
