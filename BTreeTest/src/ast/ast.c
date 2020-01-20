/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 01:20:24 by mabayle           #+#    #+#             */
/*   Updated: 2019/12/17 04:34:39 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

t_ast   *init_node(t_lex *lex)
{
    t_ast *new_node;

    new_node = ft_memalloc(sizeof(t_ast*));
    new_node->lex = lex;
    new_node->value_left = NULL;
    new_node->value_right = NULL;
    new_node->left = NULL;
    new_node->right = NULL;

    return (new_node);
}

void    init_priority(t_lex *lex)
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
            lex->priority = 2;
        else if (lex->operator == DAND || lex->operator == DPIPE)
            lex->priority = 3;
        else
            lex->priority = 0;
        //printf("[DEBUG][PRIORITY]\n   Value du maillon : | %s |\n   Valeur de token : | %u |\n   Valeur de priority : | %d |\n", lex->value, lex->operator, lex->priority);
        lex = lex->next;
    }
}

int     build_ast(t_lex *lex, t_ast *ast)
{
    init_priority(lex);
    if (lex && lex->token != UNKNOWN)
    {
        ast = init_node(lex);
        create_ast(ast, 3);
        ft_putast(ast);
    }
    return (0);
}