/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 05:19:31 by mabayle           #+#    #+#             */
/*   Updated: 2020/03/19 01:10:28 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

/*
** Purpose of the function : Use ft_strcmp(<token_value>, <SEARCH>) and if
**							function return 0 assigns a new type to my token
** Return value : no return
*/

void	is_operator(t_lex *new)
{
	if (new->token != 0)
		return ;
	new->token = CONTROL_OPE;
	if (ft_strcmp(new->value, ";") == 0)
		new->operator = SEMIC;
	else if (ft_strcmp(new->value, ";;") == 0)
		new->operator = DSEMIC;
	else if (ft_strcmp(new->value, "|") == 0)
		new->operator = PIPE;
	else if (ft_strcmp(new->value, "||") == 0)
		new->operator = DPIPE;
	else if (ft_strcmp(new->value, "&") == 0)
		new->operator = AND;
	else if (ft_strcmp(new->value, "&&") == 0)
		new->operator = DAND;
	else
		new->token = 0;
}

/*
** Purpose of the function : Use ft_strcmp(<token_value>, <SEARCH>) and if
**							function return 0 assigns a new type to my token
** Return value : no return
*/

void	is_redirection(t_lex *new)
{
	if (new->token != 0)
		return ;
	new->token = REDIR_OPE;
	if (ft_strcmp(new->value, ">") == 0)
		new->operator = GREAT;
	else if (ft_strcmp(new->value, ">>") == 0)
		new->operator = DGREAT;
	else if (ft_strcmp(new->value, "<") == 0)
		new->operator = LESS;
	else if (ft_strcmp(new->value, "<<") == 0)
		new->operator = DLESS;
	else if (ft_strcmp(new->value, "<>") == 0)
		new->operator = LESS_GREAT;
	else if (ft_strcmp(new->value, ">&") == 0)
		new->operator = GREAT_AND;
	else if (ft_strcmp(new->value, "<&") == 0)
		new->operator = LESS_AND;
	else if (ft_strcmp(new->value, ">|") == 0)
		new->operator = CLOBBER;
	else if (ft_strcmp(new->value, "<<-") == 0)
		new->operator = DLESS_DASH;
	else if (ft_strcmp(new->value, "&>") == 0)
		new->operator = GREAT_AND;
	else
		new->token = 0;
}

/*
** Purpose of the function : Check if my token is an assignment_word
** Steps  : 1 - Check error case (no "=" inside new->value or start with a
**				digit)
**			2 - Default : If all characters before '=' form a valid name
**				token ASSIGN_WORD shall be returned
** Return value : no return
*/

void	is_assignword(t_lex *new)
{
	int		i;

	i = 0;
	if (!new->value)
		return ;
	if (new->token != 0 || ft_strchr(new->value, '=') == 0
			|| (new->value[i] >= '0' && new->value[i] <= '9'))
		return ;
	while (new->value[i] && new->value[i] != '=')
	{
		if (new->value[i] != '_' && ft_isalnum(new->value[i]) == 0)
			return ;
		i++;
	}
	new->token = ASSIGN_WORD;
}

/*
** Purpose of the function : Assigns a type
** Steps  : 1 - First check IO_NUMBER value
**			2 - Newline case : set token type and change new->value
**			3 - Test control and redirection operator
**			4 - Special case for ASSIGN_WORD (posix grammar)
**			5 - Terminal token case (UNKNOWN type)
** Return value : no return
*/

void	token_type(t_lex *new, int io_nbr, int assignword)
{
	if (io_nbr != 0)
		new->token = IO_NUMBER;
	if (new->value != NULL && *new->value == '\n')
	{
		new->token = NEW_LINE;
		ft_strdel(&new->value);
		new->value = ft_strdup("NEWLINE");
	}
	new->operator = 0;
	is_operator(new);
	is_redirection(new);
	if (assignword == 0)
	{
		is_assignword(new);
		if (new->token != ASSIGN_WORD)
			assignword = 1;
	}
	if (new->token == CONTROL_OPE)
		assignword = 0;
	if (new->value == NULL)
	{
		new->token = UNKNOWN;
		new->value = ft_strdup("_EOI_");
	}
}
