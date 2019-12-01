/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 00:07:35 by mabayle           #+#    #+#             */
/*   Updated: 2019/11/29 02:16:16 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"

/*
** Objectif de la fonction : check if lex->next->value == WORD
** Valeur de retour : return 1 if match | else return 0
*/
int     filename(t_lex *lex)
{
    if (lex->token == WORD)
        return (1);
    else
        return (0);
}