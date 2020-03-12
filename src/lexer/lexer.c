/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 04:48:49 by mabayle           #+#    #+#             */
/*   Updated: 2020/03/12 05:17:23 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

/*
** Purpose of the function : Find end index (for actual token)
** Steps  : 1 - While input exist or input[i] is not : newline, space, tab or
**				an operator
**			2 - Special case : Skip backslash
**			3 - Quote case : Call the dedicated function
**			4 - Default : increment i
** Return value : Token end index
*/

int		find_end(int i, char *input)
{
	while (input[i] && input[i] != '\n' && !ft_is_separator(input[i])
			&& !check_operator(input + i))
	{
		if (input[i] == '\\')
			i++;
		if (input[i] == '\'' || input[i] == '"' || (input[i] == '$'
				&& input[i + 1] == '{'))
		{
			i = quote_brace_case(i, input);
			break ;
		}
		if (input[i])
			i++;
	}
	return (i);
}

/*
** Purpose of the function : Find end index (for actual token)
** Steps  : 1 - Skip newline
**			2 - Digit case : find end (with or without space after) and check
**				if next token is a redirection operator (ex : >>). If that's the
**				case actual token is a IO_NUMBER
**			3 - Check if actual token is an operator (redirection or control)
**			4 - Error case : if prev token is &> or <& ignore et continue to
**				search
**			5 - Default case : search end index (with other function)
** Return value : Token end index
*/

int		end_case_index(t_lex *lex, char *input, int *io_nbr)
{
	int		i;
	t_lex	*last;

	i = 0;
	if (input[i] == '\n')
		while (input[i] == '\n')
			i++;
	else if (ft_isdigit(input[i]) == 1)
	{
		while (ft_isdigit(input[i]) == 1)
			i++;
		!ft_strncmp(input + i, ">", 1) || !ft_strncmp(input + i, "<", 1)
				? *io_nbr = 1 : (i = find_end(i, input));
	}
	else if ((i = check_operator(input)))
		;
	else if (*input == '-')
	{
		last = lex_last(lex);
		i = last && (last->operator == GREAT_AND || last->operator == LESS_AND)
			? 1 : find_end(i, input);
	}
	else
		i = find_end(i, input);
	return (i);
}

/*static char	*create_token(char *input, int i)
{
	char	*token;
	char	*tmp;

	if (ft_strchr(input, '\\') != NULL)
	{
		while (input[i] != '\\')
			i++;
		tmp = ft_strsub(input, 0, i);
		i++;
	}
	else
	{
		ft_strsub(input, 0, i);
	}
	return (token);
}*/

/*
** Purpose of the function : Fill in my node and add it to my list
** Steps  : 1 - get value for my future lexeme
**			2 - Create a new node and fill lex->value with token
**			3 - Give a type (WORD, OPERATOR, ...)
**			4 - Add new node to my list
**			5 - Free variable token
**			6 - Upgrade lex_size
** Retrun value : no return
*/

void	valid(t_lex **lex, char *input, int io, int i)
{
	char	*token;
	t_lex	*new;
	int		aword;

	aword = 0;
	//token = ft_strsub(input, 0, i);
	token = create_token(input, i);
	new = list_new(token);
	inserer gestion inhib ici
	token_type(new, io, aword);
	list_add(lex, new);
	ft_strdel(&token);
	g_shell->lex_size++;
}

/*
** Purpose of the function : Split input string in lexemes and add them to my
**							list.
** Steps  : 1 - Error case : missing quote (:118) or input == NULL
**			2 - Add last token EOI (End Of Input)
**			3 - Print debug (if 21sh is launch with "DEBUG" has argument)
**			4 - Call ft_parse (check posix grammar and create AST)
**			5 - Free my linked list
** Return value : no return
*/

void	ft_lexer(t_lex **lex, char *input)
{
	int		i;
	int		io_nbr;

	if (!lex || !input)
		return ;
	while (*input)
	{
		while (ft_is_separator(*input) == 1)
			input++;
		io_nbr = 0;
		i = end_case_index(*lex, input, &io_nbr);
		if (i != -1)
			valid(lex, input, io_nbr, i);
		else
		{
			lexdel(lex);
			ft_putendl("[DEBUG] Exception");
			return ;
		}
		input = input + i++;
	}
	g_shell->lex_size != 0 ? valid(lex, "__EOI__", io_nbr, 0) : 0;
	g_shell->lex && g_shell->debug == 1 ? ft_print_header(&(g_shell->lex)) : 0;
	ft_parse(&g_shell->lex);
	lexdel(lex);
}
