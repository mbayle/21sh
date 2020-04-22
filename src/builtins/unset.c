/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 14:43:46 by ymarcill          #+#    #+#             */
/*   Updated: 2020/04/22 14:43:49 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int	delete_loc_first(t_myloc *loc)
{
	t_myloc	*save;

	ft_strdel(&loc->next->key);
	ft_strdel(&loc->next->val);
	ft_strdel(&loc->next->keyval);
	save = loc;
	loc = loc->next;
	ft_memdel((void**)&save);
	if (loc)
		g_jobcontrol.myloc = loc;
	else
		g_jobcontrol.myloc = NULL;
	return (0);
}

int	delete_loc(char *keyval)
{
	char	**tmp;
	t_myloc *loc;
	t_myloc *save;

	tmp = ft_strsplit(keyval, '=');
	loc = g_jobcontrol.myloc;
	if (!ft_strcmp(loc->key, tmp[0]))
		delete_loc_first(loc);
	while (loc)
	{
		if (loc->next && !ft_strcmp(loc->next->key, tmp[0]))
		{
			ft_strdel(&loc->next->key);
			ft_strdel(&loc->next->val);
			ft_strdel(&loc->next->keyval);
			save = loc->next;
			loc->next = loc->next->next;
			ft_memdel((void**)&save);
			ft_freetab(tmp);
			return (0);
		}
		loc = loc->next;
	}
	ft_freetab(tmp);
	return (1);
}

int	unsetloc(char **cmd)
{
	int	i;

	i = 1;
	if (!cmd)
		return (0);
	while (cmd[i])
	{
		delete_loc(cmd[i]);
		delete_env(cmd[i]);
		i++;
	}
	return (0);
}
