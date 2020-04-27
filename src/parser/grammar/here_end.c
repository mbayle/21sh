/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 05:07:46 by mabayle           #+#    #+#             */
/*   Updated: 2020/04/27 19:34:21 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

/*
** Purpose of the function : check if lex->next->value == WORD and apply
**							rule 3 of posix grammar :
**							Quote removal shall be applied to the word to
**							determine the delimiter that is used to find the
**							end of the here-document that begins after the
**							next <newline>
** Valeur de retour : return 1 if match | else return 0
*/

int		here_end(t_lex *lex)
{
	char *new;

	new = NULL;
	if (lex->token == WORD)
	{
		if (lex->value[0] == '"')
		{
			if (ft_strlen(lex->value) > 0)
			{
				new = ft_memalloc(ft_strlen(lex->value) + 1);
				ft_strcpy(new, lex->value++);
			}
			else if (ft_strlen(new) > 1)
				new[ft_strlen(new) - 2] = '\0';
			ft_strdel(&new);
			return (1);
		}
	}
	return (0);
}
