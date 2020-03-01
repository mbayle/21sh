/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:11:48 by ymarcill          #+#    #+#             */
/*   Updated: 2020/02/20 01:17:26 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"
#include "../includes/jobcontrol.h"
int			execute_builtin(char **cmd)
{
	if (ft_strcmp(cmd[0], "jobs") == 0)
	   	 g_jobcontrol.ret = ft_jobs(g_jobcontrol.first_mail, cmd);
	else if (ft_strcmp(cmd[0], "fg") == 0)
   		 g_jobcontrol.ret = put_in_fg(1, g_jobcontrol.first_mail, cmd);
	else if (ft_strcmp(cmd[0], "bg") == 0)
		g_jobcontrol.ret = put_in_bg(g_jobcontrol.first_mail, 1, cmd, g_jobcontrol.first_job->first_process);
	return (0);
}

int		child_process(int oldlink[2], int newlink[2], char *mypath, char **cmd)
{
	char	**av;
	pid_t	pid;

	pid = -1;
	av = tab_copy(g_jobcontrol.av);
	if (((mypath && ft_strcmp(mypath, "b")) ||  (ft_strcmp(mypath, "b") == 0 && av[g_jobcontrol.i + 1] )) && (pid = fork()) == 0)
	{
		ft_putnbr(g_jobcontrol.g_fg);
		if (g_jobcontrol.g_fg)
			reset_attr();
		set_id_sign(g_jobcontrol.g_fg);
		fill_pipe(oldlink, newlink, av, g_jobcontrol.i);
		if (parse_redir(av[g_jobcontrol.i], 1) == NULL)
		{
			mypath = NULL;
			exit(g_jobcontrol.ret = 1);
		}
		if (ft_strcmp(mypath, "b") == 0)
		{
		 	execute_builtin(cmd);
			exit(g_jobcontrol.ret);
		}
		if (ft_strcmp(mypath, "b") != -1 && ft_strcmp(mypath, "b") != 0)
			execve(mypath, cmd, g_jobcontrol.env);
	}
	ft_freetab(g_jobcontrol.av);
	return (pid);
}

t_process	*father_process(char **av, t_process *pro, int oldlink[2], int newlink[2])
{
	pid_t	pid;
	char	**cmd;
	char	*mypath;

	if (g_jobcontrol.ret == -42)
		return (NULL);
	ft_putnbr(g_jobcontrol.i);
	ft_putendl(av[g_jobcontrol.i]);
	cmd = parse_redir(av[g_jobcontrol.i], 0);
	cmd = check_assign(cmd);
	mypath = my_path(cmd, g_jobcontrol.env);
	if (ft_strcmp(mypath, "b") == 0 && !av[g_jobcontrol.i + 1])
		execute_builtin(cmd);
	g_jobcontrol.av = tab_copy(av);
	pid = child_process(oldlink, newlink, mypath, cmd);
	close_fd_father(oldlink, newlink);
	ft_freetab(cmd);
	if (mypath)
		pro = fill_jc_struc(pid, av[g_jobcontrol.i], pro);
	ft_strdel(&mypath);
	return (pro);
}

void	exec_process(char **av, int i)
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
			oldlink[0]  = newlink[0];
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

int		pipe_exec(char **av, char **env, int fg)
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
		put_in_bg(g_jobcontrol.first_job, 0, NULL, g_jobcontrol.first_job->first_process);
	return (0);
}
