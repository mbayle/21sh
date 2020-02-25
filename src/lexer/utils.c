/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 05:21:12 by mabayle           #+#    #+#             */
/*   Updated: 2020/02/25 04:46:09 by mabayle          ###   ########.fr       */
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

/*
** Purpose of the function : Looking for final quote
** Return value : return index of last quote (if match) else return -1 (error)
*/

int		quote_case(int i, char *input)
{
	if (input[i] == '\'')
	{
		i++;
		while (input[i] && input[i] != '\'')
			i++;
		input[i] != 39 ? i = -1 : i++;
	}
	if (input[i] == '"')
	{
		i++;
		while (input[i] && input[i] != 34)
		{
			if (input[i] == 92 && input[i + 1])
				i = i + 2;
			else
				i++;
		}
		input[i] != 34 ? i = -1 : i++;
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
