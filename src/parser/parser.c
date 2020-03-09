/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 04:00:43 by mabayle           #+#    #+#             */
/*   Updated: 2020/03/09 11:50:27 by mabayle          ###   ########.fr       */
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
		lex = lex->next;
	}
	return (NULL);
}

char	*value_env(char *input, int i)
{
	char	*new;

	new = ft_strdup("");
	while (input[i] && !ft_isspace(input[i]) && input[i] != '$' &&
			input[i] != ':' && input[i] != '"')
		new = ft_strjoin_onef(new, input[i++]);
	return (new);
}

char	*dquote_expand(char *input)
{
	int		i;
	char 	*var;
	char	*new;

	i = 0;
	new = ft_strdup("");
	while (input[i])
	{
		if (input[i] == '$' && ft_strlen(input) > 1)
		{
			var = value_env(input, i++ + 1);
			new = ft_strjoin_free(new, ((getenv(var)) ? getenv(var) : "\0"));
			free(var);
			while (input[i] && !ft_isspace(input[i]))
				i++;
			input[i] ? new = ft_strjoin_onef(new, ' ') : 0;
		}
		// INSERER BOUCLE DE LECTURE DES VARIABLES LOCALES ICI
		else
			new = ft_strjoin_onef(new, input[i]);
		i++;
	}
	input[0] == '"' && input[i] != '"' ? new = ft_strjoin_onef(new, '"') : 0;
	ft_putstr(L_BLUE);
	ft_putstr("    Echo special case ! Old / New value for token->next : ");
	ft_putstr(WHITE);
	ft_putendl(new);
	return (new);
}

char	*is_in_env(char *search)
{
	while (g_lined->env)
	{
		if (ft_strcmp(g_lined->env->varn, search) == 0)
			return (g_lined->env->var);
		g_lined->env = g_lined->env->next;
	}
	return (0);
}

#include <stdio.h>
char	*dollar_expand(char *value)
{
	char *new;

	new = ft_strdup("");

	if (value[0] == '$')
		new = is_in_env(&value[1]);
	printf("Value de getenv pour la valeur = %s\n", &value[1]);
	// INSERER BOUCLE POUR LES VARIABLES LOCALES ICI
	ft_putstr(L_BLUE);
	ft_putstr("    Dollar expansion work ! New value for lexeme : ");
	ft_putstr(WHITE);
	ft_putendl(new);
	return (new);
}

char	*tilde_expand(char *value)
{
	char *new;

	new = ft_strdup("");
	if (value[0] == '~')
	{
		if (value[1] == '+')
			new = ft_strjoin_free(new, getenv("PWD"));
		else if (value[1] == '-')
			new = ft_strjoin_free(new, getenv("OLDPWD"));
		else
			new = ft_strjoin_free(new, getenv("HOME"));	
		if (ft_strlen(value) >= 1 && value[1] == '/')
			new = ft_strjoin_free(new, &value[1]);
	}
	ft_putstr(L_BLUE);
	ft_putstr("    Tilde expansion work ! New value for lexeme : ");
	ft_putstr(WHITE);
	ft_putendl(new);
	return (ft_strlen(new) >= 1 ? new : value);
}

void	verify_expansion(t_lex *lex)
{
	ft_putstr(PURPLE);
	ft_putendl("Expansion debug :");
	ft_putstr(WHITE);
	while (lex)
	{
		ft_putendl_col("Searching, please wait...", L_GRAY, WHITE);
		if (lex->value[0] == '~')
			lex->value = tilde_expand(lex->value);
		else if (lex->value[0] == '$')
			lex->value = dollar_expand(lex->value);
		else if (lex->value[0] == '"')
			lex->value = dquote_expand(lex->value);
		else
			ft_putendl_col("No expand symbol in this token", L_YELLOW, WHITE);
		lex = lex->next;
	}
	write(1, "\n", 1);
}

/*
** Purpose of the function : Check error and after check posix grammar. If
**							everything is ok call build_ast
** Return value : If an error is found return 0, else return 1
*/

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
		build_ast(g_shell->lex, &g_shell->ast);
	return (1);
}
