/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:11:48 by ymarcill          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/03/12 13:52:58 by frameton         ###   ########.fr       */
=======
/*   Updated: 2020/03/12 04:03:28 by ymarcill         ###   ########.fr       */
>>>>>>> ce249d80ba63912b7485ba780508bb524d42216d
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

void			exec_b(char **cmd)
{
	if (ft_strcmp(cmd[0], "test") == 0)
		g_jobcontrol.ret = ft_test(cmd, 0, NULL);
	if (ft_strcmp(cmd[0], "export") == 0)
		g_jobcontrol.ret = exec_export(&g_jobcontrol.s, cmd);
	if (ft_strcmp(cmd[0], "alias") == 0)
		g_jobcontrol.ret = exec_alias(cmd);
//	if (ft_strcmp(cmd[0], "cd") == 0)
//		g_jobcontrol.ret = fonction val;
	if (ft_strcmp(cmd[0], "unalias") == 0)
		g_jobcontrol.ret = exec_unalias(cmd);
	if (ft_strcmp(cmd[0], "exit") == 0)
		exit_edl(&g_jobcontrol.s, cmd);
	if (ft_strcmp(cmd[0], "env") == 0)
		g_jobcontrol.ret = exec_env(&g_jobcontrol.s);
	if (ft_strcmp(cmd[0], "jobs") == 0)
		g_jobcontrol.ret = ft_jobs(g_jobcontrol.first_mail, cmd);
	if (ft_strcmp(cmd[0], "set") == 0)
		g_jobcontrol.ret = exec_set(&g_jobcontrol.s, cmd);
	else if (ft_strcmp(cmd[0], "fg") == 0)
		g_jobcontrol.ret = put_in_fg(1, g_jobcontrol.first_mail, cmd);
	else if (ft_strcmp(cmd[0], "bg") == 0)
		g_jobcontrol.ret = put_in_bg(g_jobcontrol.first_mail, 1, cmd,
				g_jobcontrol.first_job->first_process);
}

int				execute_builtin(char **cmd)
{
	char	*tmp;

	tmp = get_line(g_jobcontrol.env);
	if (!cmd || !cmd[0])
		return (g_jobcontrol.ret = 1);
	if (ft_strcmp(cmd[0], "setcpt") == 0)
		g_jobcontrol.ret = exec_setcpt(&g_jobcontrol.s);
	if (ft_strcmp(cmd[0], "type") == 0)
		g_jobcontrol.ret = exec_type(cmd);
	if (ft_strcmp(cmd[0], "history") == 0)
		g_jobcontrol.ret = exec_history(g_jobcontrol.s);
	if (ft_strcmp(cmd[0], "help") == 0)
		g_jobcontrol.ret = exec_sethelp();
	if (ft_strcmp(cmd[0], "setenv") == 0)
		g_jobcontrol.ret = exec_setenv(&g_jobcontrol.s, cmd, NULL, 1);
	if (ft_strcmp(cmd[0], "unsetenv") == 0)
		g_jobcontrol.ret = exec_unsetenv(&g_jobcontrol.s, cmd);
	if (ft_strcmp(cmd[0], "unset") == 0)
		g_jobcontrol.ret = exec_unset(&g_jobcontrol.s, cmd);
	if (ft_strcmp(cmd[0], "hash") == 0)
		g_jobcontrol.ret = exec_hash(&g_jobcontrol.h_tab, tmp, cmd + 1);
	exec_b(cmd);
	ft_strdel(&tmp);
	return (0);
}

int				child_process(int oldlink[2], int newlink[2], char *mypath,
		char **cmd)
{
	pid_t	pid;

	pid = -1;
	if (mypath && (((ft_strcmp(mypath, "b") != 0) || (ft_strcmp(mypath, "b")
					== 0 && g_jobcontrol.sim == 1))) && (pid = fork()) == 0)
	{
		do_in_child(oldlink, newlink, g_jobcontrol.arg);
		parse_redir(g_jobcontrol.arg[g_jobcontrol.i], 1);
		if (g_jobcontrol.sim == 1 && g_jobcontrol.g_fg)
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
	return (pid);
}

char			**do_red_ass_exp_quo(char **cmd, char **av)
{
//	EXPANDRE av
	cmd = parse_redir(av, 0);
//	cmd = parse_redir(av[g_jobcontrol.i], 0);
//	INSERT QUOTE_REMOVAL HERE
	if (g_jobcontrol.sim == 0 && g_jobcontrol.g_fg)
		cmd = check_assign(cmd);
	else
		cmd = del_one(cmd, just_ass(cmd));
	if (cmd && cmd[0] && ft_strcmp(cmd[0], "env") == 0 && is_env_arg(cmd))
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
	char	*tmp;

	cmd = NULL;
	if (!should_i_exec())
		return (NULL);
	cmd = do_red_ass_exp_quo(cmd, av);
	mypath = my_path(cmd, g_jobcontrol.env);
	if (g_jobcontrol.sim == 0)
		execute_builtin(cmd);
	pid = child_process(oldlink, newlink, mypath, cmd);
	close_fd_father(oldlink, newlink);
	g_jobcontrol.red = 0;
	unexec_asign();
	ft_freetab(cmd);
	tmp = concat_tab(av);
	if (mypath)
		pro = fill_jc_struc(pid, tmp, pro);
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
	save_fd();
	while (av && av[i])
	{
		if (av && av[i] && av[i][0] && ft_strcmp(av[i][0], "|") == 0)
			i++;
		else
		{
			oldlink[0] = newlink[0];
			if (av && av[i] &&  av[i + 1] && av[i + 1][0] && ft_strcmp(av[i + 1][0], "|") == 0)
				if (pipe(newlink) < 0)
					ft_putendl_fd("Could not create the pipe", 2);
			g_jobcontrol.i = i;
			if (!(pro = father_process(av[i], pro, oldlink, newlink)))
				return ;
			i++;
		}
	}
	reset_fd();
}

int				pipe_exec(char ***av, char **env, int fg)
{
	int	i;
	(void)env;
	i = 0;

	if (g_jobcontrol.env)
		ft_freetab(g_jobcontrol.env);
	g_jobcontrol.env = env_copy(g_jobcontrol.s.env);
	g_jobcontrol.first_job->first_process = NULL;
	g_jobcontrol.first_job->fg = fg;
	exec_process(av, i);
	if (fg)
		put_in_fg(0, g_jobcontrol.first_mail, NULL);
	else
		put_in_bg(g_jobcontrol.first_job, 0, NULL,
				g_jobcontrol.first_job->first_process);
	ft_freetab(g_jobcontrol.av);
	ft_putstr("\nRET: ");
	ft_putnbr(g_jobcontrol.ret);
	return (0);
}
