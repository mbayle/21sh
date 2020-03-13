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

char	**env_copy(t_lst2 *menv)
{
	int		i;
	char	**dst;

	i = 0;
	if (!(dst = malloc(sizeof(char*) * ((elst_size(menv) + 1)))))
		return (NULL);
	while (menv)
	{
		if (menv->lcl == 0)
			dst[i++] = ft_strdup(menv->env);
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
		unexec_ass(g_jobcontrol.ass);
		exec_ass(g_jobcontrol.ass_stock);
		g_jobcontrol.assi = 0;
	}
}

int		should_i_exec(void)
{
	if (g_jobcontrol.ao == 1)
	{
		g_jobcontrol.ao = 0;
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
