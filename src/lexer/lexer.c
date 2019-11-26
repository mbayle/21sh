/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 04:48:49 by mabayle           #+#    #+#             */
/*   Updated: 2019/11/26 02:08:56 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

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
		check_redirection(input + i) >= 1 ? *io_nbr = 1 : find_end(i, input);
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
			ft_putendl("Synthax Error");
			lexdel(lex);
			break;
		}
		input = input + i++;
	}

	/*****  DEBUG *****/
	while ((*lex))
	{
		ft_putendl("[DEBUG][LEXER.C][FT_LEXER][VALUE]");
		ft_putstr("   VALUE DU TOKEN => ");
		ft_putendl((*lex)->value);
		ft_putstr("   TYPE DE TOKEN => ");
		ft_print_debug(lex);
		(*lex) = (*lex)->next;
	}
	/*****  FIN DEBUG ******/
	// Fonction add history a rajouter si ft_parser ok
	lexdel(lex);
	return ;
}
