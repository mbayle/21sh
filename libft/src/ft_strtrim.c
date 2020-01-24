/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 10:12:15 by mabayle           #+#    #+#             */
/*   Updated: 2019/03/03 06:44:51 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t		start;
	size_t		stop;

	if (!s)
		return (NULL);
	start = 0;
	while (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
		start++;
	stop = ft_strlen(s);
	while ((s[stop - 1] == ' ' || s[stop - 1] == '\n' || s[stop - 1] == '\t') &&
			stop > start)
		stop--;
	if (start == 0 && stop == ft_strlen(s))
		return (ft_strdup(s));
	else if (start == stop)
		return (ft_strdup(""));
	else
		return (ft_strsub(s, start, stop - start));
}
