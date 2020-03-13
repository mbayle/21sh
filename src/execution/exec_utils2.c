/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 02:53:20 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/12 22:53:53 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		is_env_arg(char **cmd)
{
	int i;

	i = 1;
	while (cmd[i])
	{
		if (ft_occur(cmd[i], '-') == 0 && ft_occur(cmd[i], '=') == 0)
			return (i);
		i++;
	}
	return (0);
}

char	**check_opt_env(char **cmd)
{
	int		i;
	int		y;
	char	**dst;

	i = 0;
	y = 0;
	if (!(dst = malloc(sizeof(char*) * (tab_size(cmd) + 1))))
		return (NULL);
	while (cmd[i])
	{
		if (ft_occur(cmd[i], '-') || ft_occur(cmd[i], '='))
			i++;
		if (cmd[i])
			dst[y++] = ft_strdup(cmd[i++]);
	}
	dst[y] = NULL;
	ft_freetab(cmd);
	return (dst);
}
