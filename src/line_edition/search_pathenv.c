/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_pathenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 02:16:57 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 02:16:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

char	*search_pathenv(t_lst2 *l)
{
	char	s[5];
	char	*new;

	s[0] = 'P';
	s[1] = 'A';
	s[2] = 'T';
	s[3] = 'H';
	s[4] = '\0';
	new = NULL;
	while (l)
	{
		if (l->varn && (ft_strcmp(s, l->varn)) == 0)
			return (ft_strdup(l->env));
		l = l->next;
	}
	return (NULL);
}
