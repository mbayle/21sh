/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 05:21:12 by mabayle           #+#    #+#             */
/*   Updated: 2019/09/09 02:13:25 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int		check_redirection(char *input)
{
	if (!ft_strncmp(input, "<<-", 3))
		return (3);
	else if (!ft_strncmp(input, ">>", 2) || !ft_strncmp(input, "<<", 2)
		|| !ft_strncmp(input, "<&", 2) || !ft_strncmp(input, ">&", 2)
		|| !ft_strncmp(input, "<>", 2) || !ft_strncmp(input, ">|", 2))
		return (2);
	else if (*input == '>' || *input == '<')
		return (1);
	else
		return (0);
}

int		check_operator(char *input)
{
	if (!ft_strncmp(input, "<<-", 3))
		return (3);
	else if (!ft_strncmp(input, ";;", 2) || !ft_strncmp(input, ">>", 2)
		|| !ft_strncmp(input, "<<", 2) || !ft_strncmp(input, ">&", 2)
		|| !ft_strncmp(input, "<&", 2) || !ft_strncmp(input, "||", 2)
		|| !ft_strncmp(input, "&&", 2) || !ft_strncmp(input, "<>", 2)
		|| !ft_strncmp(input, ">|", 2))
		return (2);
	else if (*input == '|' || *input == ';' || *input == '>'
				|| *input == '<' || *input == '&')
		return (1);
	else
		return (0);
}

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

int		ft_is_separator(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}
