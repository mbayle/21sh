/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 02:44:00 by mabayle           #+#    #+#             */
/*   Updated: 2020/04/22 15:26:14 by ymarcill         ###   ########.fr       */
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
		if (lex->operator == PIPE)
			lex->priority = 1;
		else if (lex->operator == SEMIC || lex->operator == AND
				|| lex->token == NEW_LINE)
			lex->priority = 3;
		else if (lex->operator == DAND || lex->operator == DPIPE)
			lex->priority = 2;
		else
			lex->priority = 0;
		lex = lex->next;
	}
}

void	astdel(t_ast **ast)
{
	if (*ast)
	{
		if ((*ast)->left)
			astdel(&(*ast)->left);
		if ((*ast)->right)
			astdel(&(*ast)->right);
		(*ast)->lex ? lexdel(&(*ast)->lex) : 0;
		(*ast)->lex = NULL;
		(*ast)->left = NULL;
		(*ast)->right = NULL;
		free(*ast);
		*ast = NULL;
	}
}
