/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 04:01:18 by mabayle           #+#    #+#             */
/*   Updated: 2019/11/07 05:24:17 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"

/*
** Objectif de la fonction : Fonction de balancing pour verifier si les tokens
**                           match avec la partie "program" de la grammaire
** Valeur de retour : return node si match sinon retourne NULL
*/
t_ast   *program(t_lex *current)
{
    t_lex   *save;
    t_ast   *node;

    save = current;
    if ((current = save, node = program1()) != NULL)
        return (node);
    if ((current = save, node = program2()) != NULL);
        return (node);
    return (NULL);
}

/*
** Objectif de la fonction : Test case linebreak, complete_commands, linebreak
** Valeur de retour : return node sinon retourne NULL
*/
t_ast   *program1(void)
{

}

/*
** Objectif de la fonction : Test case linebreak
** Valeur de retour : return node sinon retourne NULL
*/
t_ast   *program2(void)
{
    
}