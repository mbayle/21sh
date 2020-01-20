/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 01:37:00 by mabayle           #+#    #+#             */
/*   Updated: 2019/12/17 04:56:38 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"
#include "lexer.h"

static int	has_priority(t_lex *lex, int priority)
{
	while (lex)
	{
		if (lex->priority == priority)
			return (1);
		lex = lex->next;
	}
	return (0);
}

void    split_lex(t_ast *ast, int priority)
{
    t_lex   *tmp;
    t_lex   *tmp_left;
    t_lex   *tmp_right;

    tmp = g_shell->lex;
    tmp_left = NULL;
    tmp_right = NULL;
    if (!g_shell->lex || g_shell->lex_size <= 1)
        return ;
    while (tmp->next)
    {
        if (tmp->next->priority == priority)
        {
            tmp_left = tmp->next;
            tmp_right = tmp;
        }
        tmp = tmp->next;
    }
    ast->right = init_node(tmp_left->next);
	tmp_left ? tmp_left->next = NULL : 0;
	tmp_right ? tmp_right->next = NULL : 0;
	ast->left = init_node(ast->lex);
	ast->lex = tmp_left;
    printf("[DEBUG]\n\tValue de tmp : |%s|\n\tValue de tmp_left : |%s|\n\tValue de tmp_right : |%s|\n", tmp->value, tmp_left->value, tmp_right->value);
}

void    create_ast(t_ast *ast, int priority)
{
    if (ast)
    {   
        if (has_priority(g_shell->lex, 3) == 1)
        {
            split_lex(ast, priority);
            ft_putendl("[DEBUG][SPLIT_LEX] Fonction split_lex ok");
        }    
        if (ast->right)
        {
            printf("[DEBUG][CREATE_AST]\n   Value de depart de ast_right : | %s |\n", ast->right->value_right->value);
            create_ast(ast->right, priority);
        }    
        if (ast->left)
            create_ast(ast->left, priority);
    }
}