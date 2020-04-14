/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ari_ast_operands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 04:41:51 by geargenc          #+#    #+#             */
/*   Updated: 2020/04/14 06:21:29 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int				ft_ari_ast_value(t_ari_ast *ast)
{
	if (ast->current &&
		!(g_ari_asttab[ast->current->token].type & ARI_TYPE_OP))
		return (-1); // erreur syntaxe
	ft_ari_ast_insert_child(ast);
	return (0);
}

int				ft_ari_ast_par_rt(t_ari_ast *ast)
{
	t_ari_node	*next;

	if (!ast->current ||
		(g_ari_asttab[ast->current->token].type & ARI_TYPE_OP))
		return (-1); // operande attendu
	while (ast->current &&
		!(g_ari_asttab[ast->current->token].type & ARI_TYPE_SUB))
		ast->current = ast->current->parent;
	if (ast->current)
	{
		next = ast->list->right;
		free(ast->list);
		ast->list = next;
		ast->current->token = ARI_PAR_RT;
	}
	else
		return (-1); // operande attendu
	return (0);
}
