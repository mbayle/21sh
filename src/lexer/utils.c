/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 05:21:12 by mabayle           #+#    #+#             */
/*   Updated: 2020/04/20 15:54:50 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

/*
** Purpose of the function : Search the next characters match with a redirection
**							operator
** Return value : if match return size of the operator | else return 0
*/

int		check_redir(char *input)
{
	if (!ft_strncmp(input, "<<-", 3))
		return (3);
	else if (!ft_strncmp(input, ">>", 2) || !ft_strncmp(input, "<<", 2)
		|| !ft_strncmp(input, "<&", 2) || !ft_strncmp(input, ">&", 2)
		|| !ft_strncmp(input, "<>", 2) || !ft_strncmp(input, ">|", 2)
		|| !ft_strncmp(input, "&>", 2))
		return (2);
	else if (*input == '>' || *input == '<')
		return (1);
	else
		return (0);
}

/*
** Purpose of the function : Search the next characters match with an operator
** Return value : if match return size of the operator | else return 0
*/

int		check_operator(char *input)
{
	if (!input)
		return (0);
	if (!ft_strncmp(input, "<<-", 3))
		return (3);
	else if (!ft_strncmp(input, ";;", 2) || !ft_strncmp(input, ">>", 2)
		|| !ft_strncmp(input, "<<", 2) || !ft_strncmp(input, ">&", 2)
		|| !ft_strncmp(input, "<&", 2) || !ft_strncmp(input, "||", 2)
		|| !ft_strncmp(input, "&&", 2) || !ft_strncmp(input, "<>", 2)
		|| !ft_strncmp(input, ">|", 2) || !ft_strncmp(input, "&>", 2))
		return (2);
	else if (*input == '|' || *input == ';' || *input == '>'
				|| *input == '<' || *input == '&')
		return (1);
	else
		return (0);
}

static int     test_squote(char *input)
{
    int     dquote;
    int     i;
	char	stack[256];
	int		ret;

    dquote = 0;
    i = 0;
    while (input[i])
    {
		if ((input[i] == '$' && input[i + 1] == '{')
		|| (input[i] == '$' && input[i + 1] == '('))
		{
			ret = ft_bracket(input + i, -1, 0, stack);
			if (ret > 0)
				i = i + ret + 1;
		}
        if (input[i] == 39)
        {
            if (dquote == 1)
                dquote = 0;
            else
                dquote = 1;
        }
        if (dquote == 0 && (input[i] == ' ' || check_operator(input + i) > 0))
            break ;
        i++;
    }
	return (i);
}

static int     test_dquote(char *input)
{
    int     dquote;
    int     i;
	char	stack[256];
	int		ret;

    dquote = 0;
    i = 0;
    while (input[i])
    {
		if ((input[i] == '$' && input[i + 1] == '{')
		|| (input[i] == '$' && input[i + 1] == '('))
		{
			ret = ft_bracket(input + i, -1, 0, stack);
			if (ret > 0)
				i = i + ret + 1;
			else
				return (-1);
		}
        if (input[i] == 92)
            i = i + 2;
        if (input[i] == 34)
        {
            if (dquote == 1)
                dquote = 0;
            else
                dquote = 1;
        }
        if (dquote == 0 && (input[i] == ' ' || check_operator(input + i) > 0))
			break ;
        i++;
    }
	return (i);
}

/*
** Purpose of the function : Looking for final quote
** Return value : return index of last quote (if match) else return -1 (error)
*/

int		quote_brace_case(int i, char *input)
{
	char	stack[256];
	int		ret;

	if (input[i] == '\'')
		i = test_squote(input);
	if (input[i] == '"')
		i = test_dquote(input);
	if ((input[i] == '$' && input[i + 1] == '{')
		|| (input[i] == '$' && input[i + 1] == '('))
	{
		ret = ft_bracket_index(input, -1, 0, stack);
		if (ret > 0)
			i = i + ret + 1;
		else
			return (ret);
		if (input[i] && check_operator(input + i) == 0)		
 			while (input[i] && input[i] != ' ' && check_operator(input + i) == 0)		
 				i++;
	}
	return (i);
}

/*
** Purpose of the function : Check function
** Return value : return 1 if it's a space or a tab | else return 0
*/

int		ft_is_separator(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}
