/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 04:00:43 by mabayle           #+#    #+#             */
/*   Updated: 2020/03/12 05:21:16 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

/*
** Purpose of the function : Find next token (skip newline)
** Return value : return lexeme
*/

t_lex	*next_token(t_lex *lex)
{
	lex = lex->next;
	while (lex && lex->token == NEW_LINE)
		lex = lex->next;
	return (lex);
}

/*
** Purpose of the function : Check obvious error case
** Return value : if an error is found return  lex->value (error message)
**				if no error return NULL
*/

char	*check_tokenerror(t_lex *lex)
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
		{
			if (lex->next->token == UNKNOWN)
				return (lex->value);
			else
				return (lex->next->value);
		}
		if (lex->token == CONTROL_OPE && (next_tok = next_token(lex))
				&& next_tok->token == CONTROL_OPE)
			return (next_tok->value);
		if (lex->operator == PIPE && (next_tok = next_token(lex))
				&& next_tok->token == UNKNOWN)
			return (lex->value);
		lex = lex->next;
	}
	return (NULL);
}

/*
** Purpose of the function : Check error and after check posix grammar. If
**							everything is ok call build_ast
** Return value : If an error is found return 0, else return 1
*/

t_lex	*check_heredoc(t_lex *lex)
{
	char	*tmp;

	while (lex)
	{
		if (lex->operator == DLESS)
		{
			lex = lex->next;;
			tmp = heredoc(lex->value);
			ft_strdel(&lex->value);
			lex->value = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
		if (lex)
			lex = lex->next;  
	}
	return (lex);
//	save_fd();
//	tmp = lex_to_tab(lex);
//	do_heredoc(tmp);
//	ft_freetab(tmp);
}

int		ft_parse(t_lex **lex)
{
	t_lex	*current;
	char	*error;

	current = *lex;
	error = NULL;
	if (g_shell->lex_size == 0)
		return (0);
	if ((error = check_tokenerror(current)) != NULL)
	{
		ft_putstr(RED);
		ft_putstr("42sh: parse error near: '");
		ft_putstr(error);
		ft_putendl("'");
		ft_putstr(WHITE);
		return (0);
	}
	current = *lex;
	if (current && current->token != UNKNOWN && program(current) == 0)
	{
		ft_putstr(RED);
		ft_putendl("42sh: parse error");
		ft_putstr(WHITE);
	}
	else
	{
		check_heredoc(g_shell->lex);
		build_ast(g_shell->lex, &g_shell->ast);
	}
	return (1);
}
