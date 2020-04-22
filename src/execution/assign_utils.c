/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 15:09:52 by ymarcill          #+#    #+#             */
/*   Updated: 2020/04/22 15:09:56 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

char	*fill_keyval(char *ass)
{
	char	**tmp;
	char	*dst;
	char	*t;

	tmp = ft_strsplit(ass, '=');
	t = ft_simple_expanse(tmp[1]);
	dst = ft_strjoin(tmp[0], "=");
	dst = ft_strjoinfree(dst, t);
	ft_strdel(&t);
	ft_strdel(&tmp[0]);
	ft_strdel(&tmp[1]);
	ft_memdel((void**)&tmp);
	return (dst);
}

int		fill_tab_stock_env(char *ass, int y)
{
	t_myenv	*menv;
	char	*clean_ass;
	char	**tmp;

	menv = g_jobcontrol.myenv;
	while (menv)
	{
		clean_ass = ft_strdup(ass + 1);
		tmp = ft_strsplit(clean_ass, '=');
		if (ft_strcmp(menv->key, tmp[0]) == 0)
			g_jobcontrol.ass_stockenv[y++] = ft_strdup(menv->keyval);
		ft_freetab(tmp);
		ft_strdel(&clean_ass);
		menv = menv->next;
	}
	return (y);
}

void	save_ass(char **ass)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	if (g_jobcontrol.ass)
		ft_freetab(g_jobcontrol.ass);
	if (!(g_jobcontrol.ass = malloc(sizeof(char *) * (just_ass(ass) + 1))))
		return (malloc_exit());
	while (ass[i] && ass[i][0] == '\r')
		g_jobcontrol.ass[y++] = ft_strdup(ass[i++]);
	g_jobcontrol.ass[y] = NULL;
}

char	**cpy_env_plus(char **ass)
{
	int		i;
	int		y;
	char	**tmp2;

	i = 1;
	y = 0;
	if (!(tmp2 = malloc(sizeof(char*) * (tab_size(ass) + 2))))
		malloc_exit();
	tmp2[0] = NULL;
	if (ass)
	{
		tmp2[0] = ft_strdup("setenv");
		while (ass[y])
			tmp2[i++] = ft_strdup(ass[y++]);
		tmp2[i] = NULL;
	}
	i == 1 ? ft_memdel((void**)&tmp2) : 0;
	return (tmp2);
}
