/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_backslash_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:40:51 by geargenc          #+#    #+#             */
/*   Updated: 2020/03/21 06:52:12 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_count_quotes(char *word, bool dquote)
{
	int		i;
	int		quotes;

	i = 0;
	quotes = 0;
	while (word[i])
	{
		if (word[i] == '\\' || word[i] == '\"' || (word[i] == '\'' && !dquote))
			quotes++;
		i++;
	}
	return (quotes);
}

char		*ft_backslash_quotes(char *word, bool dquote)
{
	char	*res;
	int		i;
	int		quotes;

	quotes = ft_count_quotes(word, dquote);
	if (!quotes)
		return (word);
	res = (char *)malloc_exit((ft_strlen(word) + quotes + 1) * sizeof(char));
	i = 0;
	quotes = 0;
	while (word[i])
	{
		if (word[i] == '\\' || word[i] == '\"' || (word[i] == '\'' && !dquote))
		{
			res[i + quotes] = '\\';
			quotes++;
		}
		res[i + quotes] = word[i];
		i++;
	}
	res[i + quotes] = '\0';
	free(word);
	return (res);
}
