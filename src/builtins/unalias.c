/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:35:07 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/09 22:42:59 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		uprint_error(char *key)
{
	if (key)
	{
		ft_putstr_fd("Shell: unalias", 2);
		ft_putstr_fd(key, 2);
		ft_putendl_fd(": not found", 2);
	}
	else
	{
		ft_putendl_fd("unalias: usage: unalias [-a] name [name ...]", 2);
	}
	return (-1);
}

int		del_first(t_alias *al)
{
	t_alias	*tmp;

	ft_strdel(&al->key);
	ft_strdel(&al->value);
	tmp = al;
	al = al->next;
	ft_memdel((void**)tmp);
	g_jobcontrol.alias = al;
	return (0);
}

int		del_alias(char *key)
{
	t_alias *tmp;
	t_alias *link;

	link = g_jobcontrol.alias;
	if (link)
	{
		ft_putstr("linkkey -->");
		ft_putendl(link->key);
		ft_putstr("kkey -->");
		ft_putendl(key);
	}
	if (link && link->key && key && ft_strcmp(link->key, key) == 0)
		return (del_first(link));
	while (link)
	{
		if (link->next && ft_strcmp(link->next->key, key) == 0)
		{
			ft_putendl("I FOUND IT");
			ft_putendl(link->next->key);
			ft_strdel(&link->next->key);
			ft_strdel(&link->next->value);
			tmp = link->next;
			if (link->next && link->next->next == NULL)
				g_jobcontrol.alias = link;
			link->next = link->next->next;
			ft_memdel((void**)tmp);
			return (0);
		}
		link = link->next;
	}
	return (uprint_error(key));
}

void	del_all(t_alias *al)
{
	printf("%s %p\n", "adressde g_alias: ", g_jobcontrol.alias);
	printf("%s %p\n", "adressde al: ", al);
	if (!al)
		return ;
	if (al->next)
		del_all(al->next);
	ft_strdel(&al->key);
	ft_strdel(&al->value);
	ft_memdel((void**)&al);
}

int		exec_unalias(char **cmd)
{
	int i;
	int	ret;

	i = 1;
	ret = 0;
	if (!cmd[1])
		return (uprint_error(NULL));
	if (cmd[i] && cmd[i][0] == '-')
	{
		if (ft_strcmp(cmd[i], "-a") == 0)
			del_all(g_jobcontrol.alias);
		else
			return (uprint_error(NULL));
	}
	else if (cmd[i])
	{
		ft_putendl("In my loop");
		while (cmd[i])
			ret = del_alias(cmd[i++]);	
	}
	return (ret);
}
