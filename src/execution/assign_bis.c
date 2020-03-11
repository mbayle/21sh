/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:37:48 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/11 21:48:37 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

char	**del_one(char **tabl, int pos)
{
	int		i;
	int		j;
	char	**dst;

	i = 0;
	j = 0;
	if (!(dst = malloc(sizeof(char*) * (tab_size(tabl) + 1))))
		return (NULL);
	while (tabl[i] && i < pos)
		i++;
	while (tabl[i])
		dst[j++] = ft_strdup(tabl[i++]);
	dst[j] = NULL;
	return (dst);
}

int		just_ass(char **ass)
{
	int i;

	i = 0;
	while (ass[i])
	{
		if (ass[i][0] != '\r')
			return (i);
		i++;
	}
	return (-1);
}

void	exec_ass(char **ass)
{
	int		i;
	char	*tmp;

	i = 0;
	while (ass && ass[i] && ass[i][0] == '\r')
	{
		tmp = ft_strdup(ass[i]);
		free(ass[i]);
		ass[i] = ft_strdup(tmp + 1);
		i++;
	}
	if (ass)
		g_jobcontrol.ret = exec_setenv(&g_jobcontrol.s, ass, NULL, 0);
}

char	**get_key(char **ass)
{
	int		i;
	int		y;
	char	**tmp;
	char	**dst;

	i = 0;
	y = 1;
	if (!(dst = malloc(sizeof(char*) * (tab_size(ass) + 2))))
		return (NULL);
	dst[0] = ft_strdup("unset");
	while (ass[i])
	{
		tmp = ft_strsplit(ass[i], '=');
		dst[y] = ft_strdup(tmp[0]);
		ft_freetab(tmp);
		i++;
		y++;
	}
	dst[y] = NULL;
	return (dst);
}

char	**move_char(char **ass)
{
	int		i;
	char	*tmp;

	i = 0;
	while (ass[i])
	{
		if (ass[i][0] == '\r')
		{
			tmp = ft_strdup(ass[i]);
			ft_strdel(&ass[i]);
			ass[i] = ft_strdup(tmp + 1);
		}
		i++;
	}
	return (ass);
}
