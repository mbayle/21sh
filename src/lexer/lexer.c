/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 04:48:49 by mabayle           #+#    #+#             */
/*   Updated: 2020/03/11 19:36:02 by ymarcill         ###   ########.fr       */
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
			i = quote_bksl_case(i, input);
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
// Malloc not protected
void	valid(t_lex **lex, char *input, int io, int i)
{
	char	*token;
	t_lex	*new;
	int		aword;

	aword = 0;
	token = ft_strsub(input, 0, i);
	new = list_new(token);
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


char	**lex_to_tab(t_lex *lex)
{
	int		i;
	char	**dst;

	i = 0;
	if (!(dst = malloc(sizeof(char*) * (lex_size(lex) + 1))))
		return (NULL);
	while (lex && lex->token != UNKNOWN)
	{
		if (lex->token == IO_NUMBER)
		{
			dst[i] = ft_strjoin(lex->value, lex->next->value);
			lex = lex->next;
		}
		else
        	dst[i] = ft_strdup(lex->value);
		i++;
		lex = lex->next;
	}
	dst[i] = NULL;
	return (dst);
}

/*void	do_heredoc(char **cmd)
{
	int	i;
	int	ret;
	int	nb;

	i = 0;
	nb= 0;
	g_jobcontrol.here = 0;
	nb_heredoc(cmd);
	while (cmd[i])
	{
		if (ft_seq_occur(cmd[i], "<<"))
		{
	//		printf("%s %s\n", "cmd[i]", cmd[i]);
	//		printf("%s %s\n", "cmd[i + 1]", cmd[i + 1]);
			nb++;
			ret = myheredoc(cmd[i], cmd[i + 1], nb);
		}
		if (ret == -1)// && (g_jobcontrol.ret = 1) == 1)
			return ;
		i++;
	}
}*/

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
			return ;
		}
		input = input + i++;
	}
	g_shell->lex_size != 0 ? valid(lex, "__EOI__", io_nbr, 0) : 0;
	g_shell->lex && g_shell->debug == 1 ? ft_print_header(&(g_shell->lex)) : 0;
	ft_parse(&g_shell->lex);
	lexdel(lex);
}












