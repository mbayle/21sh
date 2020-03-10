/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 00:07:10 by mabayle           #+#    #+#             */
/*   Updated: 2020/03/10 00:56:37 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

/*
** take a valid parameter expansion, isolate param in expression and expand it
** return value, or NULL if unset
*/
char	*parameter_get_param(char *input)
{
	char	*end;
	char	save;
	char	*param;

	end = ft_strpbrk(input, ":+-=?#%");
	save = *end;
	*end = '\0';
	if ((param = getenv(input)))
		;
	else if ((param = search_varloc(input)))
		;
	else
		param = NULL;
	*end = save;
	return (param);
}

char	*parameter_get_word(char *input)
{
	char	*start;
	char	*word;

	start = ft_strpbrk(input, ":+-=?#%");
	if (*start == ':')
		start++;
	else if ((*start == '#' || *start == '%') && (*start == start[1]))
		start++;
	if ((word = getenv(start)))
		;
	else if ((word = search_varloc(start)))
		;
	else
		word = NULL;
	return (word);
}

char	*parameter_minus(input)
{
	char	*param;
	char	*word;

	param = parameter_get_param(input);
	word = parameter_get_word(input);
	if (!param)
		;
	else if (!*param)
		;
	else
		;
}

char	*parameter_expansion(char *input)
{
	int 	i;
	char	save;
	char	*res;

	i = 0;
	while(input[i] && input[i] == '}')
		i++;
	if (!input[i])
		return (NULL);
	save = input[i];
	input[i] = '\0';
	if (ft_strstr(":-", input) || ft_strstr("-", input))
		res = parameter_minus(input);
	else if (ft_strstr(":=", input) || ft_strstr("=", input))
		res = parameter_equal(input);
	else if (ft_strstr(":?", input) || ft_strstr("?", input))
		res = parameter_quest(input);
	else if (ft_strstr(":+", input) || ft_strstr("+", input))
		res = parameter_plus(input);
	else if (ft_strstr("#", input) || ft_strstr("##", input))
		res = parameter_hash(input);
	else if (ft_strstr("%", input) || ft_strstr("%%", input))
		res = parameter_percent(input);
	else
		res = NULL;
	input[i] = save;
	return (res);
	// look for format
	// switch
	// return res foud
}