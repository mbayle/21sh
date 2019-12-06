/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserV2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 04:00:43 by mabayle           #+#    #+#             */
/*   Updated: 2019/12/06 04:39:55 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** TO DO LIST : - Faire toutes les fonctions selon la gram posix
*/

#include "parser.h"
#include "grammar.h"
#include "lexer.h"


t_lex	*ft_next_token(t_lex *lex)
{
	lex = lex->next;
	while (lex && lex->token == NEW_LINE)
		lex = lex->next;
	return (lex);
}

/*
** ft_check_tokenerror :
** Check les erreurs de syntax.
** Renvoie une chaine de char correspondant au token responsable de l'erreur de
** syntaxe.
** Renvoie NULL si aucune erreur n'est trouvée.
*/

char		*ft_check_tokenerror(t_lex *lex)
{
	t_lex	*next_tok;

	if (lex && lex->token == CONTROL_OPE)
		return (lex->value);
	while (lex)
	{
		if (lex->operator == DSEMIC || lex->operator == CLOBBER
			|| lex->operator == LESS_GREAT || lex->operator == DLESS_DASH)
			return (lex->value);
		if (lex->token == REDIR_OPE && lex->next && lex->next->token != WORD)
			return (lex->next->value);
		if (lex->token == CONTROL_OPE && (next_tok = ft_next_token(lex))
			&& next_tok->token == CONTROL_OPE)
			return (next_tok->value);
		lex = lex->next;
	}
	return (NULL);
}


int	ft_parse(t_lex **lex, t_ast **ast)
{
	(void) ast;
	t_lex	*current;
	char	*error;

	current = *lex;
	error = NULL;
	if (g_shell->lex_size == 0)
		return (-1);
	ft_putstr(PURPLE);
	ft_putendl("Parser debug :");
	ft_putstr(NC);
	if ((error = ft_check_tokenerror(current)) != NULL)
	{
		ft_putstr(RED);
		ft_putstr("42sh: parse error near: '");
		ft_putstr(error);
		ft_putendl("'");
		ft_putstr(NC);
		return (0);
	}
	current = *lex;
	if (program(current) == 0)
	{
		ft_putstr(RED);
		ft_putstr("42sh: parse error");
		ft_putstr(NC);
	}
	else
	{
		ft_putstr(GREEN);
        ft_putendl("No parse error");
        ft_putstr(NC);
	}
	return (1);
}
