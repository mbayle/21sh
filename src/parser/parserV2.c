/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserV2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 04:00:43 by mabayle           #+#    #+#             */
/*   Updated: 2019/12/05 01:56:24 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** TO DO LIST : - Faire toutes les fonctions selon la gram posix
*/

#include "parser.h"
#include "grammar.h"
#include "lexer.h"

int	ft_parse(t_lex **lex, t_ast **ast)
{
	(void) ast;
	t_lex	*current;

	current = *lex;
	//*ast = program(current);
	if (g_shell->lex_size == 0)
		return (-1);
	ft_putendl("[DEBUG][FT_PARSE] Ok avant program");
	if (program(current) == 0)
	{
		ft_putendl("parse error");
	}
	return (1);
}
