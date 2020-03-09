/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 22:50:21 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/09 09:19:53 by frameton         ###   ########.fr       */
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
		/*g_jobcontrol.first_job->last_ret = ft_set.c*/
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
		/*g_jobcontrol.first_job->last_ret = ft_unset.c*/
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

/*void	save_ass_stock(char **ass)
  {
  int	i;
  int	x;
  int	y;
  char	**tmp;

  i = 0;
  x = 0;
  y = 0;
  if (!(g_jobcontrol.ass_stock = malloc(sizeof(char*) * (just_ass(ass) + 1))))
  return ;
  while (ass[i] && i < just_ass(ass))
  {
  while (localstr[x]) // ta struct de var locale
  {
  tmp = ft_strsplit(localstr[x], '=');
//	if (ft_strcmp(tmp, ass[i]) == 0)
g_jobcontrol.ass_stock[y++] = ft_strdup(localstr[x]);
x++;
}
x = 0;
i++;
}
g_jobcontrol.ass_stock[y] = NULL
}*/

char	**ass_arg(char **ass, int i)
{
	if ((i = just_ass(ass)) == -1)/*&& pas de ARGV)*/
	{
	/*	g_jobcontrol.ret= ft_export.c();*/
	}
	else /*ex: a=b c=d ls -l*/
	{
	/*	g_jobcontrol.assi = i;
		save_ass_stock(ass);
		jenregistre mes assignement de ma commande qui sont deja present dans
																	la struct
		save_ass(ass);// jenreigstre mes assig de command
		exec_ass(ass);
	//	parcour structu var local et stock ass qui existent
	//	set tout assign
	//	APRES EXEc: unset tous assign de la cmd, reset mon stock*/
	/*	ft_printtab(ass);*/
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
