/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 05:21:12 by mabayle           #+#    #+#             */
/*   Updated: 2020/04/20 16:33:41 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int		test_bracket(char *input, int i)
{
	char	stack[256];
	int		ret;

	if ((input[i] == '$' && input[i + 1] == '{')
		|| (input[i] == '$' && input[i + 1] == '('))
	{
		ret = ft_bracket_index(input + i, -1, 0, stack);
		if (ret > 0)
			i = i + ret + 1;
	}
	return (i);
}

int		test_squote(char *input)
{
	int		dquote;
	int		i;

	dquote = 0;
	i = 0;
	while (input[i])
	{
		if ((i = test_bracket(input, i)) < 0)
			return (test_bracket(input, i));
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

int		test_dquote(char *input)
{
	int		dquote;
	int		i;

	dquote = 0;
	i = 0;
	while (input[i])
	{
		if ((i = test_bracket(input, i)) < 0)
			return (test_bracket(input, i));
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
