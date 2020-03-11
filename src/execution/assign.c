/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 22:50:21 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/11 13:40:21 by ymarcill         ###   ########.fr       */
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
	while (ass && ass[i] && ass[i][0] == '\r')
	{
		tmp = ft_strdup(ass[i]);
		free(ass[i]);
		ass[i] = ft_strdup(tmp + 1);
		i++;
	}
	if (ass)
	{
		ft_putendl("\n\nEXEC ASS");
		ft_printtab(ass);
		g_jobcontrol.ret = exec_setenv(&g_jobcontrol.s, ass, NULL, 0);
	}
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
	ft_putendl("IN GET KEY ASS");
	ft_printtab(dst);
	return (dst);
}

void	unexec_ass(char **ass)
{
	int		i;
	char	*tmp;
	char	**dst;

	i = 0;
	while (ass && ass[i] && ass[i][0] == '\r')
	{
		tmp = ft_strdup(ass[i]);
		free(ass[i]);
		ass[i] = ft_strdup(tmp + 1);
		i++;
	}
	dst = get_key(ass);
	ft_putendl("IN EXEC ASS");
	ft_printtab(dst);
	g_jobcontrol.ret = exec_unset(&g_jobcontrol.s, dst);
	ft_freetab(dst);
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
	if (g_jobcontrol.ass_stock)
		ft_freetab(g_jobcontrol.ass_stock);
	if (!(g_jobcontrol.ass_stock = malloc(sizeof(char*) * (just_ass(ass) + 1))))
		return ;
	while (ass[i] && i < just_ass(ass))
	{
		while (menv) // ta struct de var locale
		{
	 		tmp = ft_strsplit(menv->env, '=');
			if (menv->lcl == 0 && ft_strcmp(tmp[0], ass[i]) == 0)
				g_jobcontrol.ass_stock[y++] = ft_strdup(menv->env);
			ft_freetab(tmp);
			menv = menv->next;
		}
		menv = g_jobcontrol.s.env;
		i++;
	}
	g_jobcontrol.ass_stock[y] = NULL;
	ft_putnbr(y);
	ft_putendl("IN SAVE ASS STOCK");
	ft_printtab(g_jobcontrol.ass_stock);
	ft_putendl("-----------");
	if (y == 0)
		ft_memdel((void**)&g_jobcontrol.ass_stock);
	//ft_printtab(g_jobcontrol.ass_stock);
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
	int		t;

	t = just_ass(ass);
	tmp = tab_copy(ass);
	if ((i = just_ass(ass)) == -1)/*&& pas de ARGV)*/
	{
		g_jobcontrol.assi = 0;
		ass= move_char(ass);
		g_jobcontrol.ret= exec_setenv(&g_jobcontrol.s, ass, NULL, 0);
		return (tmp);
	}
	else /*ex: a=b c=d ls -l*/
	{
//		ft_putendl("ARG");
//		ft_putnbr(ass[0][0]);
//		ft_putendl("-----");
//		ft_putnbr(just_ass(ass));
//		ft_putendl("-----");
//		ft_putnbr(just_ass(ass));
		g_jobcontrol.assi = i;
		save_ass_stock(ass);
//		ft_putnbr(ass[0][0]);
//		ft_putstr("  ");
		save_ass(ass);// jenreigstre mes assig de command
//		ft_putnbr(ass[0][0]);
//		ft_putstr("  ");
		exec_ass(ass);
//		ft_putnbr(ass[0][0]);
//		ft_putstr("  ");
//		ft_printtab(ass);
	}
	ft_putendl("SAVE ASS");
	ft_printtab(g_jobcontrol.ass);
	ft_putendl("SAVE ASS SOTCK");
	ft_printtab(g_jobcontrol.ass_stock);
//	ft_putnbr(ass[0][0]);
//		ft_putnbr(just_ass(ass));
	ass = del_one(ass, t);
//	ft_putendl("print ASS");
//	ft_printtab(ass);
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
