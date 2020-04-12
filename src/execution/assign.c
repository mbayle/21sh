/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 22:50:21 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/12 22:58:22 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

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

int		fill_tab_stock(char *ass, int y)
{
	t_lst2	*menv;
	char	*clean_ass;
	char	**tmp;

	menv = g_jobcontrol.s.env;
	while (menv)
	{
		clean_ass = ft_strdup(ass + 1);
		tmp = ft_strsplit(clean_ass, '=');
		if (menv->lcl == 1 && ft_strcmp(menv->varn, tmp[0]) == 0)
			g_jobcontrol.ass_stock[y++] = ft_strdup(menv->env);
		ft_freetab(tmp);
		ft_strdel(&clean_ass);
		menv = menv->next;
	}
	return (y);
}

void	save_ass_stock(char **ass)
{
	int			i;
	int			y;

	i = -1;
	y = 0;
	if (g_jobcontrol.ass_stock)
		ft_freetab(g_jobcontrol.ass_stock);
	if (!(g_jobcontrol.ass_stock = malloc(sizeof(char*) * (just_ass(ass) + 1))))
		return (malloc_exit());
	while (ass[++i] && i < just_ass(ass))
	{
		y = fill_tab_stock(ass[i], y);
		i++;
	}
	g_jobcontrol.ass_stock[y] = NULL;
	y == 0 ? ft_memdel((void**)&g_jobcontrol.ass_stock) : 0;
}

char	**exp_ass(char **ass)
{
	int		i;
	int		y;
	char	**tmp;
	char	**dst;

	i = 0;
	y = 0;
	tmp = NULL;
	if (!(dst = malloc(sizeof(char*) * (tab_size(ass) + 1))))
		malloc_exit();
	while (ass[i])
	{
		if (ass[i][0] == '\r')
		{
			tmp = ft_strsplit(ass[i], '=');
			tmp[1] = ft_simple_expanse(tmp[1]);
			dst[y] = ft_strjoin(tmp[0], "=");
			dst[y] = ft_strjoinfree(dst[y], tmp[1]);
			y++;
			i++;
			ft_strdel(&tmp[0]);
			ft_strdel(&tmp[1]);
			ft_memdel((void**)&tmp);
			//ft_freetab(tmp);
		}
		else
			dst[y++] = ft_strdup(ass[i++]);
	}
	dst[y] = NULL;
	ft_putendl("----------");
	ft_printtab(dst);
	ft_putendl("----------");

	ft_freetab(ass);
	return (dst);

}

char	**ass_arg(char **ass, int i)
{
	char	**tmp;

	tmp = NULL;
	ass = exp_ass(ass);
	if ((i = just_ass(ass)) == -1)
	{
		tmp = tab_copy(ass);
		g_jobcontrol.assi = 0;
		ass = move_char(ass);
		g_jobcontrol.ret = exec_setenv(&g_jobcontrol.s, ass, NULL, 0);
		ft_freetab(ass);
		return (tmp);
	}
	else
	{
		g_jobcontrol.assi = 1;
		save_ass_stock(ass);
		save_ass(ass);
		exec_ass(g_jobcontrol.ass, 1);
	}
	ass = del_one(ass, i);
	return (ass);
}

char	**check_assign(char **ass)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	if (!ass || !ass[i])
		return (NULL);
	if (ass[i][0] == '\r')
		ass = ass_arg(ass, i);
	else
	{
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
	}
	return (ass);
}
