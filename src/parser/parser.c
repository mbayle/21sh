/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 01:53:33 by mabayle           #+#    #+#             */
/*   Updated: 2019/10/30 04:16:59 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	check_error(t_lex *lex)
{
	t_lex *nextok;

	if (lex && lex->token == CONTROL_OPE)
		return (-1);
	while (lex)
	{
		if (lex->operator == DSEMIC || lex->operator == CLOBBER
			|| lex->operator == LESS_GREAT 
			|| lex->operator == DLESS_DASH)
			return (-1);
		if (lex->token == REDIR_OPE && lex->next 
			&& lex->next->token != WORD)
			return (-1);
		if (lex->token == CONTROL_OPE && )
	}
}

/*
** Objectif de la fonction : Check les erreurs de syntax et les inhibiteurs
**                           Supprime les tokens newline inutile
**                           Recupere les arguments des hdoc si besoin (a basculer dans la partie lexer ?)
** Valeur de retour : Return -1 si syntax error ou interruption (signal), sinon return 0
** TO DO LIST : - Fonction de check des erreurs
**		- Fonction pour la gestion des erreurs (define des messages dans un .h, free, ...)
**		- Fonction pour clear les newline
**		- Fonction de print si le flag debug est actif (activation via argv ou en command line ?) 
*/

int	parser(t_lex **lex)
{
	int	parse_error;

	if (!lex)
		return (0);
	if ((parse_error = check_error(*lex)) != 0)
	{
		ft_error(parse_error);
		return (-1);
	}
}
