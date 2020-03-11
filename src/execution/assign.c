/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 22:50:21 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/11 21:24:13 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

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
	char		*t;
	char		**tmp;
	t_lst2		*menv;

	i = 0;
	y = 0;
	menv = g_jobcontrol.s.env;
	if (g_jobcontrol.ass_stock)
		ft_freetab(g_jobcontrol.ass_stock);
	if (!(g_jobcontrol.ass_stock = malloc(sizeof(char*) * (just_ass(ass) + 1))))
		return ;
	ft_putnbr(just_ass(ass));
	while (ass[i] && i < just_ass(ass))
	{
		ft_putendl("IN THE LOOP");
		while (menv) // ta struct de var locale
		{
			t = ft_strdup(ass[i] + 1);
			ft_putnbr(t[0]);
	 		tmp = ft_strsplit(t, '=');
			if (ft_strcmp(menv->varn, tmp[0]) == 0)
			{
				ft_putendl("HEYEYEYEY");
				ft_putendl(menv->varn);
				ft_putendl(tmp[0]);
			}
			if (menv->lcl == 0 && ft_strcmp(menv->varn, tmp[0]) == 0)
				g_jobcontrol.ass_stock[y++] = ft_strdup(menv->env);
			ft_freetab(tmp);
			menv = menv->next;
		}
		menv = g_jobcontrol.s.env;
		i++;
	}
	g_jobcontrol.ass_stock[y] = NULL;
	y == 0 ? ft_memdel((void**)&g_jobcontrol.ass_stock): 0;
}

char	**ass_arg(char **ass, int i)
{
	char	**tmp;
	char	**tmp2;
	int		t;

	t = just_ass(ass);
	tmp = tab_copy(ass);
	ft_putendl("NUMBER ASCCI");
	ft_putnbr(tmp[0][0]);
	ft_putstr(" : ");
	ft_putnbr(ass[0][0]);
	ft_putstr("\n\n");
	if ((i = just_ass(ass)) == -1)/*&& pas de ARGV)*/
	{
		ft_putendl("I SET");
		ft_putendl(ass[0]);
		g_jobcontrol.assi = 0;
		ass= move_char(ass);
		g_jobcontrol.ret= exec_setenv(&g_jobcontrol.s, ass, NULL, 0);
		return (tmp);
	}
	else /*ex: a=b c=d ls -l*/
	{
		g_jobcontrol.assi = 1;
		tmp2 = move_char(ass);
		ft_putendl("coucoucoucocuocucoucocucoucoucocucocuou");
		ft_putnbr(tmp2[0][0]);
		save_ass_stock(ass);
		save_ass(ass);// jenreigstre mes assig de command
		exec_ass(ass);
		//ft_freetab(tmp2);
	}
	ass = del_one(ass, t);
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
