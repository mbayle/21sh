/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 01:24:10 by mabayle           #+#    #+#             */
/*   Updated: 2020/01/21 02:07:04 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

/*
** Objectif de la fonction : check if lex->next->value == WORD and apply
**							rule 7a of posix grammar :
**							If the TOKEN does not contain the character '=',
**							rule 1 is applied. Otherwise, 7b shall be applied.
**							For information :
**							Rule 1 :
**							When the TOKEN is exactly a reserved word, the
**							token identifier for that reserved word shall
**							result. Otherwise, the token WORD shall be
**							returned. Also, if the parser is in any state
**							where only a reserved word could be the next
**							correct token, proceed as above.
**							Rule 7b :
**							Show command_word for more information
** Valeur de retour : return 1 if match | else return 0
*/

int		cmd_name(t_lex *lex)
{
	if (lex->token != WORD)
		return (0);
	else if (ft_strchr(lex->value, '=') == NULL)
		return (1);
	else if (cmd_word(lex) == 1)
		return (1);
	else
		return (0);
}
