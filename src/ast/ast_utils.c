/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 02:44:00 by mabayle           #+#    #+#             */
/*   Updated: 2020/01/20 02:46:42 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

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

void	init_priority(t_lex *lex)
{
	if (!lex)
		return ;
	while (lex)
	{
		if (lex->operator == OTHER)
			lex->priority = 0;
		else if (lex->operator == PIPE || lex->operator == DGREAT)
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

t_ast	*no_root(t_lex *lex, t_ast *ast)
{
	char *new_root;

	new_root = ast->root;
	lex->next ? lex = lex->next : 0;
	while (lex && ft_strcmp(lex->value, "_EOI_") != 0)
	{
		new_root = ft_strcat(new_root, lex->value);
		new_root = ft_strcat(new_root, " ");
		lex = lex->next;
	}
	ast->root = new_root;
	return (ast);
}
