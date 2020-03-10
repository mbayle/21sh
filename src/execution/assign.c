/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 22:50:21 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/10 15:48:31 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int		tab_size(char **s)
{
	int i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	**tab_copy(char **tabl)
{
	int		i;
	int		j;
	char	**dst;

	i = 0;
	j = 0;
	if (!(dst = malloc(sizeof(char *) * (tab_size(tabl) + 1))))
		return (NULL);
	while (tabl[i])
	{
		dst[j] = ft_strdup(tabl[i++]);
		j++;
	}
	dst[j] = NULL;
	return (dst);
}

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
	int	i;

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
	while (ass[i] && ass[i][0] == '\r')
	{
		tmp = ft_strdup(ass[i]);
		free(ass[i]);
		ass[i] = ft_strdup(tmp + 1);
		g_jobcontrol.ret = exec_setenv(&g_jobcontrol.s, ass, NULL, 0);
		i++;
	}
}

void	unexec_ass(char **ass)
{
	int		i;
	char	*tmp;

	i = 0;
	while (ass[i] && ass[i][0] == '\r')
	{
		tmp = ft_strdup(ass[i]);
		free(ass[i]);
		ass[i] = ft_strdup(tmp + 1);
				g_jobcontrol.ret = exec_setenv(&g_jobcontrol.s, ass, NULL, 0);
		i++;
	}
}

void	save_ass(char **ass)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	if (!(g_jobcontrol.ass = malloc(sizeof(char *) * (just_ass(ass) + 1))))
		return ;
	while (ass[i] && ass[i][0] == '\r')
		g_jobcontrol.ass[y++] = ft_strdup(ass[i++]);
	g_jobcontrol.ass[y] = NULL;
}

void	save_ass_stock(char **ass)
{
	int			i;
	int			y;
	char		**tmp;
	t_lst2		*menv;

	i = 0;
	y = 0;
	menv = g_jobcontrol.s.env;
	if (!(g_jobcontrol.ass_stock = malloc(sizeof(char*) * (just_ass(ass) + 1))))
		return ;
	while (ass[i] && i < just_ass(ass))
	{
		while (menv) // ta struct de var locale
		{
	 		tmp = ft_strsplit(menv->env, '=');
			if (menv->lcl == 1 && ft_strcmp(tmp[0], ass[i]) == 0)
				g_jobcontrol.ass_stock[y++] = ft_strdup(menv->env);
			ft_freetab(tmp);
			menv = menv->next;
		}
		menv = g_jobcontrol.s.env;
		i++;
	}
	g_jobcontrol.ass_stock[y] = NULL;
	ft_printtab(g_jobcontrol.ass_stock);
}

char	**move_char(char **ass)
{
	int	i;
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

char	**ass_arg(char **ass, int i)
{
	char	**tmp;

	tmp = tab_copy(ass);
	if ((i = just_ass(ass)) == -1)/*&& pas de ARGV)*/
	{
		ass= move_char(ass);
		g_jobcontrol.ret= exec_setenv(&g_jobcontrol.s, ass, NULL, 0);
		return (tmp);
	}
	else /*ex: a=b c=d ls -l*/
	{
		g_jobcontrol.assi = i;
		save_ass_stock(ass);
		save_ass(ass);// jenreigstre mes assig de command
		exec_ass(ass);
		ft_printtab(ass);
	}
	ass = del_one(ass, just_ass(ass));
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
