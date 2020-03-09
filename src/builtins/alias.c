/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 05:49:07 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/09 08:56:24 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

void	alloc_alias(void)
{
	if (!g_jobcontrol.alias)
	{
		g_jobcontrol.alias = ft_memalloc(sizeof(*g_jobcontrol.alias));
		g_jobcontrol.alias->key = NULL;
		g_jobcontrol.alias->value = NULL;
		g_jobcontrol.alias->next = NULL;
	}
}

t_alias		*set_value(t_alias *al, char *key, char *value)
{
	al->key = ft_strdup(key);
	al->value = ft_strdup(value);
	al->next = ft_memalloc(sizeof(*g_jobcontrol.alias));
	al = al->next;
	al->next = NULL;
	return (al);	
}

t_alias		*set_alias(t_alias *al, char *key, char *value)
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
			g_jobcontrol.alias->key = ft_strdup(value);
			g_jobcontrol.alias = save;
			return (al);
		}
		tmp = tmp->next;
	}
	al = set_value(al, key, value);
	return (al);
}

int		check_error_key(char *cmd)
{
	int	i;

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

char	**key_val_split(char *cmd)
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

int		print_error(char *key, int c)
{
	ft_putstr_fd("Shell: alias: ", 2);
	ft_putstr_fd(key, 2);
	if (c == -1)
		ft_putendl_fd(": invalid alias name", 2);
	if (c == 1)
		ft_putendl_fd(": not found", 2);
	return (-1);
}

void	print_k_v(char *key, char *val)
{
	ft_putstr_fd("alias: ", 1);
	ft_putstr_fd(key, 1);
	ft_putstr_fd("=\'", 1);
	ft_putstr_fd(val, 1);
	ft_putendl_fd("\'", 1);
}

int		print_value(char *key, int i)
{
	t_alias *tmp;

	tmp = g_jobcontrol.alias;
	while (tmp->next)
	{
		printf("%s %p\n", "tmp: ", tmp);
		printf("%s %d\n", "i: ", i);
		printf("%s %s %p\n", "tmp->key: ", tmp->key, tmp->key);
		if (i && key && tmp->key && ft_strcmp(tmp->key, key) == 0)
		{
			print_k_v(key, tmp->value);
			return (0);
		}
		else if (key == NULL || i == 0)
			print_k_v(tmp->key, tmp->value);
		tmp = tmp->next;
	}
	if (key)
	{
		print_error(key, 1);
		return (-1);
	}
	return (0);
}

int		exec_alias(char **cmd)
{
	int		i;
	int		ret;
	char	**tmp;
	t_alias	*al;

	i = 0;
	al = NULL;
	ret = 0;
	alloc_alias();
	al = g_jobcontrol.alias;
	if (tab_size(cmd) < 2)
		ret = print_value(NULL, 0);
	while (tab_size(cmd) >= 2 && cmd[++i])
	{
		if (ft_occur(cmd[i], '='))
		{
			tmp = key_val_split(cmd[i]);
			if (check_error_key(tmp[0]) == 1)
				ret = print_error(tmp[0], -1);
			else
				al = set_alias(al, tmp[0], tmp[1]);
		}
		else
		{
			ret = print_value(cmd[i], 1);
		}
	}
	return (ret);	
}
