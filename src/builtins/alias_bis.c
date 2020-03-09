/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:40:19 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/09 21:33:07 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

void    alloc_alias(void)
{
	if (!g_jobcontrol.alias)
	{
		g_jobcontrol.alias = ft_memalloc(sizeof(*g_jobcontrol.alias));
		g_jobcontrol.alias->key = NULL;
		g_jobcontrol.alias->value = NULL;
		g_jobcontrol.alias->next = NULL;
	}
}

t_alias     *set_value(t_alias *al, char *key, char *value)
{
	al->key = ft_strdup(key);
	al->value = ft_strdup(value);
	al->next = ft_memalloc(sizeof(*g_jobcontrol.alias));
	al = al->next;
	al->next = NULL;
	return (al);
}

t_alias     *set_alias(t_alias *al, char *key, char *value)
{
	t_alias *tmp;
	t_alias *save;

	tmp = g_jobcontrol.alias;
	save = g_jobcontrol.alias;
	while (tmp)
	{
		if (tmp->key && ft_strcmp(tmp->key, key) == 0)
		{
			g_jobcontrol.alias = tmp;
			g_jobcontrol.alias->key = ft_strdup(key);
			g_jobcontrol.alias->value = ft_strdup(value);
			g_jobcontrol.alias = save;
			return (al);
		}
		tmp = tmp->next;
	}
	al = set_value(al, key, value);
	g_jobcontrol.alias = save;
	return (al);
}

int     check_error_key(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_' && cmd[i] != '!'
			&& cmd[i] != '%' && cmd[i] != ',' && cmd[i] != '@')
		return (1);
		i++;
	}
	return (0);
}
char    **key_val_split(char *cmd)
{
	int		i;
	int		y;
	char	**tmp;

	i = 0;
	y = 0;
	if (!(tmp = malloc(sizeof(char*) * 3)) ||
	!(tmp[0] = malloc(sizeof(char) * (ft_strlen(cmd) + 1))))
		return (NULL);
	while (cmd[i] && cmd[i] != '=')
		tmp[0][y++] = cmd[i++];
	tmp[0][y] = '\0';
	if (!(tmp[1] = malloc(sizeof(char) * (ft_strlen(cmd) + 1))))
		return (NULL);
	y = 0;
	i++;
	while (cmd[i])
		tmp[1][y++] = cmd[i++];
	tmp[1][y] = '\0';
	tmp[2] = NULL;
	return (tmp);
}

