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
	{
		dst = ft_strjoinfree(dst, " ");
		dst = ft_strjoinfree(dst, cmd[i++]);
	}
	return (dst);
}

void	unexec_asign(void)
{
	if (g_jobcontrol.assi == 1)
	{
		unexec_ass(g_jobcontrol.ass);
		exec_ass(g_jobcontrol.ass_stock, 2);
		g_jobcontrol.assi = 0;
	}
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
