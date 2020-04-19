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

char		**del_one(char **tabl, int pos)
{
	int		i;
	int		j;
	char	**dst;

	i = 0;
	j = 0;
	if (!(dst = malloc(sizeof(char*) * (tab_size(tabl) + 1))))
		malloc_exit();
	while (tabl[i] && i < pos)
		i++;
	while (tabl[i])
		dst[j++] = ft_strdup(tabl[i++]);
	ft_freetab(tabl);
	dst[j] = NULL;
	return (dst);
}

int			just_ass(char **ass)
{
	int		i;

	i = 0;
	while (ass && ass[i])
	{
		if (ass[i][0] != '\r')
			return (i);
		i++;
	}
	return (-1);
}

void		exec_ass(char **ass, int env)
{
	int		i;
	char	*tmp;
	char	**tmp2;

	i = 0;
	while (ass && ass[i] && ass[i][0] == '\r')
	{
		tmp = ft_strdup(ass[i]);
		free(ass[i]);
		ass[i] = ft_strdup(tmp + 1);
		i++;
		ft_strdel(&tmp);
	}
	if (ass)
	{
		g_jobcontrol.ret = setloc(ass);
		if (env)
		{
			tmp2 = env == 1 ? cpy_env_plus(ass) :
			cpy_env_plus(g_jobcontrol.ass_stockenv);
			g_jobcontrol.ret = mysetenv(tmp2, 0);
			ft_freetab(tmp2);
		}
	}
}

char		**get_key(char **ass)
{
	int		i;
	int		y;
	char	**tmp;
	char	**dst;

	i = 0;
	y = 1;
	if (!(dst = malloc(sizeof(char*) * (tab_size(ass) + 2))))
		malloc_exit();
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

char		**move_char(char **ass)
{
	int		i;
	int		y;
	char	**dst;

	i = 0;
	y = 0;
	if (!(dst = malloc(sizeof(char*) * (tab_size(ass) + 1))))
		malloc_exit();
	while (ass[i])
	{
		if (ass[i][0] == '\r')
			dst[y++] = ft_strdup(ass[i] + 1);
		else
			dst[y++] = ft_strdup(ass[i]);
		i++;
	}
	dst[y] = NULL;
	ft_freetab(ass);
	return (dst);
}
