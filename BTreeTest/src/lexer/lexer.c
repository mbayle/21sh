/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 04:48:49 by mabayle           #+#    #+#             */
/*   Updated: 2019/12/17 04:22:59 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int		find_end(int i, char *input)
{
	while (input[i] && input[i] != '\n' && !ft_is_separator(input[i])
			&& !check_operator(input + i))
	{
		if (input[i] == '\\')
			i++;
		if (input[i] == '\'' || input[i] == '"')
		{
			i = quote_case(i, input);
			break;
		}	
		if (input[i])
			i++;
	}
	return (i);
}

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
		input[i] == ' ' ? i++ : 0;
		check_redir(input + i) >= 1 ? *io_nbr = 1 : find_end(i, input);
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

void	valid(t_lex **lex, char *input, int io, int aword, int i)
{
	char	*token;
	t_lex	*new;

	token = ft_strsub(input, 0, i);
	new = list_new(token);
	token_type(new, io, &aword);
	list_add(lex, new);
	ft_strdel(&token);
}

void	ft_lexer(t_lex **lex, char *input)
{
	int		i;
	int		io_nbr;
	int		assignword;

	assignword = 0;
	
	if (!lex || !input)
		return ;
	while (*input)
	{
		while (ft_is_separator(*input) == 1)
			input++;
		io_nbr = 0;
		i = end_case_index(*lex, input, &io_nbr);
		if (i != -1)
		{
			valid(lex, input, io_nbr, assignword, i);
			g_shell->lex_size++;
		}
		else
		{
			ft_putstr(RED);
			ft_putendl("42sh: synthax error: missing quote");
			ft_putstr(NC);
			lexdel(lex);
			return ;
		}
		input = input + i++;
	}
	t_lex *tmp = (*lex);
	(g_shell->lex_size != 0 && tmp && tmp->token != UNKNOWN) ? valid(lex, "__EOI__", io_nbr, assignword, 0) : 0;
		
	/*****  DEBUG *****/
	
	(*lex) = tmp;
	init_priority(*lex);
	(*lex) = tmp;
	if (tmp)
	{
		ft_putstr(PURPLE);
		ft_putendl("Lexer debug :");
		ft_putstr(NC);
		ft_putendl(" ---------------------------------------------------------------------------------------------------------");
		ft_putendl("|             TOKEN            	| PRIORITY |				VALUE	     			  |");
		ft_putendl(" ---------------------------------------------------------------------------------------------------------");
		while ((*lex))
		{
			ft_putstr(CYAN);
			ft_print_debug(lex);
			ft_putstr(RED);
			write(1,"  ", 2);
			ft_putnbr((*lex)->priority);
			write(1,"         ", 9);
			ft_putstr(L_BLUE);
			ft_putendl((*lex)->value);
			(*lex) = (*lex)->next;
		}
		ft_putstr(NC);
		write(1, "\n", 1);
	}

	/*****  FIN DEBUG ******/
	(*lex) = tmp;
	build_ast(g_shell->lex, g_shell->ast);
	// Fonction add history a rajouter si ft_parser ok
	lexdel(lex);
	return ;
}
