/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:45:41 by geargenc          #+#    #+#             */
/*   Updated: 2020/04/22 15:22:28 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

char		*getvar(char *var)
{
	t_myloc	*loc;

	loc = g_jobcontrol.myloc;
	while (loc)
	{
		if (ft_strcmp(loc->key, var) == 0)
			return (loc->val == NULL ? ft_strdup("") : ft_strdup(loc->val));
		loc = loc->next;
	}
	return (NULL);
}

char		*ft_getvar(char *var)
{
	void	*ptr;

	ptr = ft_get_spparam(*var);
	if (ptr)
		return (((char *(*)(void))ptr)());
	ptr = getvar(var);
	if (ptr)
		return ((char *)ptr);
	return (NULL);
}
