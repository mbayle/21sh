/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 15:10:04 by ymarcill          #+#    #+#             */
/*   Updated: 2020/04/27 20:46:23 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int			should_i_exec(char **cmd, char *mypath, int oldlink[2],
			int newlink[2])
{
	if (g_jobcontrol.ao || g_jobcontrol.stopexe)
	{
		g_jobcontrol.ao = 0;
		ft_freetab(cmd);
		ft_strdel(&mypath);
		close_fd_father(oldlink, newlink);
		return (0);
	}
	return (1);
}

char		*is_b(char **cmd)
{
	char	*mypath;
	char	*tmp;

	mypath = NULL;
	tmp = my_path(cmd, g_jobcontrol.env);
	if (!check_b(cmd) || (g_jobcontrol.cm == 1))
		mypath = ft_strdup("b");
	else if (tmp && g_jobcontrol.cm != 1)
		mypath = ft_strdup("i");
	if (tmp)
		ft_strdel(&tmp);
	return (mypath);
}

void		exec_prgrm(char **cmd, char *path)
{
	if (ft_strcmp(path, "b") == 0)
	{
		execute_builtin(cmd);
		exit(g_jobcontrol.ret);
	}
	if (ft_strcmp(path, "b") != -1 && ft_strcmp(path, "b") != 0)
	{
		execve(path, cmd, g_jobcontrol.env);
		ft_putstr_fd("42sh: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putendl_fd(" : is a directory", 2);
		reset_attr();
		exit(1);
	}
}
