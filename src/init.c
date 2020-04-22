/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 16:05:51 by ymarcill          #+#    #+#             */
/*   Updated: 2020/04/22 16:21:16 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

void		tmp_free_struct(t_struct *s)
{
	t_lst	*del;

	while ((del = (*s).lbg))
	{
		(*s).lbg = (*s).lbg->next;
		free(del);
	}
	(*s).l = NULL;
	(*s).lbg = NULL;
	(*s).tmp = NULL;
	free_dchar(&(*s).envi);
	(*s).av = NULL;
}

char		**ft_tabdup(char **av)
{
	int		i;
	char	**dst;

	i = 0;
	while (av[i])
		i++;
	if (!(dst = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = -1;
	while (av[++i])
		dst[i] = ft_strdup(av[i]);
	dst[i] = NULL;
	return (dst);
}

t_21sh		*init_shell(int debug)
{
	t_21sh		*shell;

	shell = ft_memalloc(sizeof(*shell));
	shell->lex = NULL;
	shell->lex_size = 0;
	shell->ast = NULL;
	shell->debug = debug;
	return (shell);
}

void		init_myenv(char **envp)
{
	int		i;
	t_myenv	*save;
	char	**tmp;

	i = 0;
	g_jobcontrol.myenv = ft_memalloc(sizeof(*g_jobcontrol.myenv));
	g_jobcontrol.myenv->next = NULL;
	save = g_jobcontrol.myenv;
	while (envp[i])
	{
		tmp = ft_strsplit(envp[i], '=');
		save->keyval = ft_strdup(envp[i]);
		save->key = ft_strdup(tmp[0]);
		save->val = ft_strdup(tmp[1]);
		if (envp[i + 1])
		{
			save->next = ft_memalloc(sizeof(*g_jobcontrol.myenv));
			save = save->next;
		}
		ft_freetab(tmp);
		i++;
	}
	save = NULL;
}

void		init_myloc(char **envp)
{
	int		i;
	t_myloc	*save;
	char	**tmp;

	i = 0;
	g_jobcontrol.myloc = ft_memalloc(sizeof(*g_jobcontrol.myloc));
	g_jobcontrol.myloc->next = NULL;
	save = g_jobcontrol.myloc;
	while (envp[i])
	{
		tmp = ft_strsplit(envp[i], '=');
		save->keyval = ft_strdup(envp[i]);
		save->key = ft_strdup(tmp[0]);
		save->val = ft_strdup(tmp[1]);
		if (envp[i + 1])
		{
			save->next = ft_memalloc(sizeof(*g_jobcontrol.myloc));
			save = save->next;
		}
		ft_freetab(tmp);
		i++;
	}
	save = NULL;
}
