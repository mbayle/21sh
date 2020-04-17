/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:11:48 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/19 22:02:28 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

char		*is_b(char **cmd)
{
	char	*mypath;
	char	*tmp;

	mypath = NULL;
	tmp = my_path(cmd, g_jobcontrol.env);
	if (!check_b(cmd) || (!tmp && g_jobcontrol.cm == 1))
		mypath = ft_strdup("b");
	else if (tmp && g_jobcontrol.cm != 1)
		mypath = ft_strdup("i");
	if (tmp)
		ft_strdel(&tmp);
	return (mypath);
}

int				child_process(int oldlink[2], int newlink[2], char *path,
		char **cmd)
{
	pid_t	pid;

	pid = -1;
	if (((!ft_strcmp(path, "b") && g_jobcontrol.sim) || !ft_strcmp(path, "i"))
	&& (pid = fork()) == 0)
	{
		do_in_child(oldlink, newlink, g_jobcontrol.arg);
		parse_redir(g_jobcontrol.arg[g_jobcontrol.i], 1);
		if (ft_strcmp(path, "i") == 0)
			path = my_path(cmd, g_jobcontrol.env);
		if (g_jobcontrol.sim == 1 && g_jobcontrol.g_fg)
		{
			cmd = check_assign(cmd);
			if ((path = is_b(cmd)) && !ft_strcmp(path, "i"))
			{
				ft_strdel(&path);
				path = my_path(cmd, g_jobcontrol.env);
			}
		}
		g_jobcontrol.red == -1 ? exit(g_jobcontrol.ret = 1) : 0;
		if (ft_strcmp(path, "b") == 0)
		{
			execute_builtin(cmd);
			exit(g_jobcontrol.ret);
		}
		if (ft_strcmp(path, "b") != -1 && ft_strcmp(path, "b") != 0)
		{
			execve(path, cmd, g_jobcontrol.env);
			ft_putstr_fd("Shell: Execve error: ", 2);
			ft_putendl_fd(cmd[0], 2);
			g_jobcontrol.ret = 42;
			reset_attr();
			exit(1);
		}

	}
	return (pid);
}

char			**do_red_ass_exp_quo(char **cmd, char **av, char **mypath)
{
	*mypath = NULL;
	cmd = parse_redir(av, 0);
	cmd = ft_command_to_args(cmd);
	if (g_jobcontrol.g_fg && g_jobcontrol.sim == 0)
		cmd = check_assign(cmd);
	ft_freetab(g_jobcontrol.env);
	g_jobcontrol.env = set_copy(g_jobcontrol.myloc);
	*mypath = is_b(cmd);
	if (cmd && cmd[0] && ft_strcmp(cmd[0], "env") == 0)
	{
		if (cmd[1])
		{
			ft_freetab(cmd);
			cmd = NULL;
			ft_strdel(mypath);
		}
	}
	return (cmd);
}

t_process		*father_process(char **av, t_process *pro, int oldlink[2],
		int newlink[2])
{
	pid_t	pid;
	char	**cmd;
	char	*mypath;
	char	*tmp;

	cmd = NULL;
	cmd = do_red_ass_exp_quo(cmd, av, &mypath);
	if (!should_i_exec(cmd, mypath))
		return (NULL);
	if (g_jobcontrol.sim == 0 && mypath && !ft_strcmp(mypath, "b"))
	{
		parse_redir(g_jobcontrol.arg[g_jobcontrol.i], 1);
		execute_builtin(cmd);
	}
	pid = child_process(oldlink, newlink, mypath, cmd);
	close_fd_father(oldlink, newlink);
	g_jobcontrol.red = 0;
	ft_freetab(cmd);
	tmp = concat_tab(av);
	if (mypath) //&& g_jobcontrol.cm != 1)
	{
		pro = fill_jc_struc(pid, tmp, pro);
	}
	ft_strdel(&mypath);
	ft_strdel(&tmp);
	return (pro);
}

void			exec_process(char ***av, int i)
{
	int			oldlink[2];
	int			newlink[2];
	t_process	*pro;

	pro = NULL;
	newlink[0] = -1;
	newlink[1] = -1;
	while (av && av[i])
	{
		if (av && av[i] && av[i][0] && ft_strcmp(av[i][0], "|") == 0)
			i++;
		else
		{
			oldlink[0] = newlink[0];
			if (av && av[i] && av[i + 1] && av[i + 1][0] &&
				ft_strcmp(av[i + 1][0], "|") == 0)
				if (pipe(newlink) < 0)
					ft_putendl_fd("Could not create the pipe", 2);
			g_jobcontrol.i = i;
			pro = father_process(av[i], pro, oldlink, newlink);
			i++;
		}
		unexec_asign();
	}
}

int				pipe_exec(char ***av, int fg)
{
	int	i;

	i = 0;
	save_fd();
	g_jobcontrol.first_job->first_process = NULL;
	g_jobcontrol.first_job->fg = fg;
	exec_process(av, i);
	if (fg)
		put_in_fg(0, g_jobcontrol.first_mail, NULL);
	else
		put_in_bg(g_jobcontrol.first_job, 0, NULL,
				g_jobcontrol.first_job->first_process);
//	ft_freetab(g_jobcontrol.av);
	reset_fd();
	return (0);
}
