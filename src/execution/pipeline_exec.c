/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:11:48 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/09 09:02:23 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int				execute_builtin(char **cmd)
{
	if (!cmd || !cmd[0])
	{
		return (g_jobcontrol.ret = 1);
	}
	if (ft_strcmp(cmd[0], "setcpt") == 0)
		g_jobcontrol.ret = exec_setcpt(&g_jobcontrol.s);
	if (ft_strcmp(cmd[0], "type") == 0)
		g_jobcontrol.ret = exec_type(cmd);
	if (ft_strcmp(cmd[0], "history") == 0)
		g_jobcontrol.ret = exec_history(g_jobcontrol.s);
	if (ft_strcmp(cmd[0], "help") == 0)
		g_jobcontrol.ret = exec_sethelp();
	if (ft_strcmp(cmd[0], "test") == 0)
		g_jobcontrol.ret = ft_test(cmd, 0, NULL);
	if (ft_strcmp(cmd[0], "setenv") == 0)
		g_jobcontrol.ret = exec_setenv(&g_jobcontrol.s, NULL);
	if (ft_strcmp(cmd[0], "unsetenv") == 0)
		g_jobcontrol.ret = exec_unsetenv(&g_jobcontrol.s);
	if (ft_strcmp(cmd[0], "export") == 0)
		g_jobcontrol.ret = exec_export(&g_jobcontrol.s);
	if (ft_strcmp(cmd[0], "alias") == 0)
		g_jobcontrol.ret = exec_alias(cmd);
	if (ft_strcmp(cmd[0], "exit") == 0)
		exit(0);
//		g_jobcontrol.ret = exec_env(&g_jobcontrol.s);
	if (ft_strcmp(cmd[0], "jobs") == 0)
		g_jobcontrol.ret = ft_jobs(g_jobcontrol.first_mail, cmd);
//		g_jobcontrol.ret = exec_env(&g_jobcontrol.s);
	if (ft_strcmp(cmd[0], "set") == 0)
		g_jobcontrol.ret = exec_set(&g_jobcontrol.s);
	if (ft_strcmp(cmd[0], "unset") == 0)
		g_jobcontrol.ret = exec_unset(&g_jobcontrol.s);
	else if (ft_strcmp(cmd[0], "fg") == 0)
		g_jobcontrol.ret = put_in_fg(1, g_jobcontrol.first_mail, cmd);
	else if (ft_strcmp(cmd[0], "bg") == 0)
		g_jobcontrol.ret = put_in_bg(g_jobcontrol.first_mail, 1, cmd,
				g_jobcontrol.first_job->first_process);
	return (0);
}

int				child_process(int oldlink[2], int newlink[2], char *mypath,
		char **cmd)
{
	char	**av;
	pid_t	pid;

	pid = -1;
	av = tab_copy(g_jobcontrol.av);
	if (mypath && (((ft_strcmp(mypath, "b") != 0) || (ft_strcmp(mypath, "b")
					== 0 && g_jobcontrol.sim == 1))) && (pid = fork()) == 0)
	{
		do_in_child(oldlink, newlink, av);
		if (g_jobcontrol.sim == 1)
		{
			cmd = check_assign(cmd);
			mypath = my_path(cmd, g_jobcontrol.env);
		}
		g_jobcontrol.red == -1 ? exit(g_jobcontrol.ret = 1) : 0;
		if (ft_strcmp(mypath, "b") == 0)
		{
			execute_builtin(cmd);
			exit(g_jobcontrol.ret);
		}
		if (ft_strcmp(mypath, "b") != -1 && ft_strcmp(mypath, "b") != 0)
			execve(mypath, cmd, g_jobcontrol.env);
	}
	ft_freetab(av);
	return (pid);
}

int				is_env_arg(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (ft_occur(cmd[i], '-') == 0 && ft_occur(cmd[i], '=') == 0)
			return (i);
		i++;
	}
	return (0);
}

char			**copy_u(char **cmd, int pos)
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

char			**check_opt_env(char **cmd)
{
	int		i;
	int		y;
	char	**dst;

	i = 0;
	y = 0;
	if (!(dst = malloc(sizeof(char*) * (tab_size(cmd) + 1))))
		return (NULL);
	while (cmd[i])
	{
		if (ft_occur(cmd[i], '-') || ft_occur(cmd[i], '='))
			i++;
		if (cmd[i])
			dst[y++] = ft_strdup(cmd[i++]);
	}
	dst[y] = NULL;
	ft_freetab(cmd);
	return (dst);
}

char			**do_red_ass_exp_quo(char **cmd, char **av)
{
	cmd = parse_redir(av[g_jobcontrol.i], 1);
	/*	EXPANSION a faire mtn avant les apres pour char process*/
if (g_jobcontrol.sim == 0)
		cmd = check_assign(cmd);
	else
		cmd = del_one(cmd, just_ass(cmd));
	if (ft_strcmp(cmd[0], "env") == 0 && is_env_arg(cmd))
	{
		del_one(cmd, 1);
		cmd = check_opt_env(cmd);
	}
	return (cmd);
}

t_process		*father_process(char **av, t_process *pro, int oldlink[2],
		int newlink[2])
{
	pid_t	pid;
	char	**cmd;
	char	*mypath;

	cmd = NULL;
	if (g_jobcontrol.ao == 1)
	{
		g_jobcontrol.ao = 0;
		return (NULL);
	}
	save_fd();
	cmd = do_red_ass_exp_quo(cmd, av);;
	mypath = my_path(cmd, g_jobcontrol.env);
	if (mypath && ft_strcmp(mypath, "b") == 0 && !av[g_jobcontrol.i + 1])
	{
		execute_builtin(cmd);
		ft_putendl_fd("IN NO FORK", 2);
	}
	pid = child_process(oldlink, newlink, mypath, cmd);
	ft_freetab(cmd);
	close_fd_father(oldlink, newlink);
	g_jobcontrol.red = 0;
	reset_fd();
	/*	if (g_jobcontrol.assi == 1 && g_jobcontrol.sim == 0)
		{
		unexec_ass(g_jobcontrol.ass);
		exec_ass(g_jobcontrol.ass_stock);
		g_jobcontrol.asso == 0;
		}*/
	if (mypath)
		pro = fill_jc_struc(pid, av[g_jobcontrol.i], pro);
	ft_strdel(&mypath);
	return (pro);
}

void			exec_process(char **av, int i)
{
	int			oldlink[2];
	int			newlink[2];
	t_process	*pro;

	pro = NULL;
	newlink[0] = -1;
	newlink[1] = -1;
	while (av && av[i])
	{
		if (ft_strcmp(av[i], "|") == 0)
			i++;
		else
		{
			oldlink[0] = newlink[0];
			if (av[i + 1] && ft_strcmp(av[i + 1], "|") == 0)
				if (pipe(newlink) < 0)
					ft_putendl_fd("Could not create the pipe", 2);
			g_jobcontrol.i = i;
			if (!(pro = father_process(av, pro, oldlink, newlink)))
				return ;
			i++;
		}
	}
}

int				pipe_exec(char **av, char **env, int fg)
{
	int	i;

	i = 0;
	(void)env;
	g_jobcontrol.first_job->first_process = NULL;
	g_jobcontrol.first_job->fg = fg;
	g_jobcontrol.av = tab_copy(av);
	exec_process(av, i);
	if (fg)
		put_in_fg(0, g_jobcontrol.first_mail, NULL);
	else
		put_in_bg(g_jobcontrol.first_job, 0, NULL,
				g_jobcontrol.first_job->first_process);
	ft_freetab(av);
	ft_freetab(g_jobcontrol.av);
	ft_putstr("\nRET: ");
	ft_putnbr(g_jobcontrol.ret);
	//close_fd();
	return (0);
}
