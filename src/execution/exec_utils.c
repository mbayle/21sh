/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 02:44:01 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/12 22:51:43 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		envlst_size(t_myenv *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**env_copy(t_myenv *menv)
{
	int		i;
	char	**dst;

	i = 0;
	if (!(dst = malloc(sizeof(char*) * ((envlst_size(menv) + 1)))))
		malloc_exit();
	while (menv)
	{
//		printf("%p\n", menv);
//		ft_putendl(menv->keyval);
		dst[i++] = ft_strdup(menv->keyval);
		menv = menv->next;
	}
	dst[i] = NULL;
	return (dst);
}

char	*concat_tab(char **cmd)
{
	int		i;
	char	*dst;

	i = 0;
	if (!(dst = ft_strnew(1)))
		return (NULL);
	while (cmd[i])
		dst = ft_strjoinfree(dst, cmd[i++]);
	return (dst);
}

void	unexec_asign(void)
{
	if (g_jobcontrol.assi == 1)
	{
//		ft_putendl("		ASS STOK");
//		ft_printtab(g_jobcontrol.ass_stock);
		unexec_ass(g_jobcontrol.ass);
		exec_ass(g_jobcontrol.ass_stock, 1);
		g_jobcontrol.assi = 0;
	}
//	else
//	{
//		unexec_ass(g_jobcontrol.ass);
//	}
}

int		should_i_exec(char ** cmd, char *mypath)
{
	if (g_jobcontrol.ao  || g_jobcontrol.stopexe)
	{
		g_jobcontrol.ao = 0;
		g_jobcontrol.stopexe = 0;
		ft_freetab(cmd);
		ft_strdel(&mypath);
		return (0);
	}
	return (1);
}

char	**copy_u(char **cmd, int pos)
{
	int		i;
	int		y;
	char	**dst;

	i = 0;
	y = 0;
	if (!(dst = malloc(sizeof(char*) * (tab_size(cmd) + 1))))
		return (NULL);
	while (cmd[i] && i < pos)
		dst[y++] = ft_strdup(cmd[i++]);
	dst[y] = NULL;
	return (dst);
}
