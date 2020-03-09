/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 05:49:07 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/09 11:37:27 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

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
		ft_putendl(tmp->value);
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
	t_alias	*save;

	i = 0;
	al = NULL;
	ret = 0;
	alloc_alias();
	save = g_jobcontrol.alias;
	al = g_jobcontrol.alias;
	ft_putendl(g_jobcontrol.alias->key);
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
			ft_putendl(g_jobcontrol.alias->key);
		}
		else
		{
			ret = print_value(cmd[i], 1);
		}
	}
	g_jobcontrol.alias = save;
	ft_putendl(g_jobcontrol.alias->key);
	return (ret);	
}
