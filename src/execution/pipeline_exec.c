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

int		job_is_completed(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p && p->next && p->next->next)
		p = p->next;
	if (p && (p->status >1 || p->status == -1))
		return (1);
	return (0);
}

pid_t	job_nb(int i, t_job *j)
{
	while (j->next)
	{
		if (j->j_nb == i)
			return (j->pgid);
		j = j->next;
	}
	return (0);
}

pid_t		jobs_parser(char *str, t_job *j)
{
	int		i;
	pid_t	pgid;

	i = 0;
	pgid = 0;
	while (j->next)
	{
		ft_putendl_fd(j->command, 1);
		if (((j->fg == 0 && !job_is_completed(j)) || j->stop == 1) && ft_strcmp(j->command, str) == 0)
			return (j->pgid);
		else if (((j->fg == 0 && !job_is_completed(j)) || j->stop == 1) && j->command[i] == str[i])
		{
			while (str[i] && str[i] == j->command[i])
				i++;
			if (i == ft_strlenu(str))
				pgid = j->pgid;
			i = 0;
		}
		j = j->next;
	}
	return (pgid);
}

pid_t	last_stp_job(t_job *job)
{
	t_job	*tmp;

	tmp = job->next;
	while (job &&  tmp)
	{
		if (tmp && tmp->last_j >= job->last_j)
		{
			tmp = tmp->next;
			job = job->next;
		}
		else
			tmp = tmp->next;
	}
	return (job->pgid);
}

void	print_pid(t_job *j)
{
	t_process *p;

	p = j->first_process;
	while (p)
	{
		ft_putnbr_fd(p->lpid, 1);
		p = p->next;
		if (p)
			ft_putstr_fd(" | ", 1);
	}
}

void	print_job_status(int i, t_job *j, t_job *f_job)
{
	pid_t	pgid;

	pgid = last_stp_job(f_job);
	ft_putstr_fd("[", 1);
	ft_putnbr_fd(j->j_nb, 1);
	ft_putstr_fd("]  ", 1);
	print_pid(j);
	ft_putchar(' ');
	if (pgid && pgid == j->pgid)
		ft_putstr_fd(" +", 1);
	else
		ft_putstr_fd("  ", 1);
	if (i == 1)
		ft_putstr_fd(" suspended ", 1);
	else
		ft_putstr_fd(" running ", 1);
	ft_putendl_fd(j->command, 1);
}

void	no_param_jobs(t_job *j)
{
	t_job	*save;

	save = j;
	while (j)
	{
		if (j->stop == 1)
			print_job_status(j->stop, j, save);
		else if (j->fg != 1 && !job_is_completed(j))
			print_job_status(j->stop, j, save);
		j = j->next;
	}
}

void	job_error(const char *str)
{
	ft_putstr_fd("jobs: no such job : ", 2);
	ft_putendl_fd(str, 2);
}

int		ft_jobs(t_job *j, char **av)
{
	int		i;
	pid_t	pgid;
	t_job	*save;

	i = 1;
	save = j;
	pgid = 0;
	if (g_jobcontrol.first_job && g_jobcontrol.first_job->fg == 0)
			return (2);
	if (!av[1])
		no_param_jobs(j);
	else
	{
		while (av[i])
		{
			/* si % modifier dans le lexer par le job number verifer le numero*/
			pgid = av[i][0] != '%' ? jobs_parser(av[i], save) : job_nb(ft_atoi(av[i] + 1), save);
			if (pgid == 0)
			{
				job_error(av[i]);
				return (0);
			}
			ft_putnbr_fd(pgid, 1);
			while (pgid && j->next)
			{
				if (j->pgid == pgid)
					print_job_status(j->stop, j, save);
				j = j->next;
			}
			i++;
			j = save;
		}
	}
	return (2);
}

t_job	*put_last_stp(t_job *job, int i, int l)
{
	t_job	*cpy;
	t_job	*save;

	save = g_jobcontrol.first_job;
	cpy = g_jobcontrol.first_mail;
	ft_putendl("BEFORE THE LOOP");
	if (job)
	{
		ft_putstr("MA VAL :");
		ft_putendl(job->command);
		ft_putnbr(job->pgid);
	}
	while (cpy)
	{
		ft_putstr("CPY VALUE");
		ft_putendl(cpy->command);
		if (cpy->last_j == l && job && cpy->pgid != job->pgid)
		{
			ft_putendl("IN THE COND");
			g_jobcontrol.first_job = cpy;
			g_jobcontrol.first_job->last_j = i;
			g_jobcontrol.first_job = save;
			ft_putendl("BEFORE RETURN");
			return (cpy);
		}
		cpy = cpy->next;
	}
	return (cpy);
}

int		check_jb_nb()
{
	t_job	*first;
	int		nb;

	nb = 1;
	first = g_jobcontrol.first_mail;
	while (first)
	{
		if ((first->stop == 1 || first->fg == 0) && first->pgid != g_jobcontrol.first_job->pgid)
		{
			ft_putendl("\nIM IN CHECK");
			ft_putendl(first->command);
			ft_putnbr(first->j_nb);
			nb = first->j_nb + 1;
		}
		first = first->next;
	}
	return (nb);
}

void	to_do_if_stp(t_job *job, t_job *save, int i)
{
	ft_putstr("g_job No: ");
	ft_putnbr(g_jobcontrol.first_job->j_nb);
	ft_putstr("\ng_job pgig: ");
	ft_putnbr(g_jobcontrol.first_job->pgid);
	ft_putstr("\njob pgid: ");
	ft_putnbr(job->pgid);
	if (g_jobcontrol.first_job->pgid == job->pgid && g_jobcontrol.first_job->j_nb == 0)
	{
		ft_putnbr(42);
		ft_putnbr(g_jobcontrol.repere);
		g_jobcontrol.repere += 1;
		g_jobcontrol.first_job->j_nb = check_jb_nb();
		ft_putnbr(g_jobcontrol.first_job->j_nb);
	}
	g_jobcontrol.first_job = job;
	g_jobcontrol.first_job->last_j = 2;	
	put_last_stp(put_last_stp(job, 1, 2), 0, 1);
//	put_last_stp(job, 1, 2);
	if (i)
		ft_putstr_fd("\n", 2);
	ft_putstr_fd("[", 2);
	ft_putnbr_fd(g_jobcontrol.first_job->j_nb, 2);
	ft_putstr_fd("] +  ", 2);
	ft_putnbr_fd(g_jobcontrol.first_job->pgid, 2);
	if (i)
	{
		g_jobcontrol.first_job->stop = 1;
		ft_putstr_fd("  suspended ", 2);
	}
	else
		ft_putstr_fd("  running ", 2);
	ft_putendl_fd(g_jobcontrol.first_job->command, 2);
	g_jobcontrol.first_job = save;
}

int		check_if_stop(t_process *p, t_job *job)
{
	t_job	*save;

	save = g_jobcontrol.first_job;
	while (p)
	{
		if (p->status == 1)
		{
			to_do_if_stp(job, save, 1);
			return (1);
		}
		if (job->fg != 1)
		{
			to_do_if_stp(job, save, 0);
			return (1);
		}

		p = p->next;
	}
	return (0);
}

int		process_status(pid_t pid, int status, t_process *p)
{
	t_process *pro;

	pro = g_jobcontrol.first_job->first_process;
	g_jobcontrol.first_job->first_process = p;
	if (pid < 0)
	//	g_jobcontrol.first_job->first_process->status = g_jobcontrol.ret;
		return (-1);
	if (WIFEXITED(status) == TRUE)
	{
		g_jobcontrol.first_job->first_process->status = status ? status : 2;
		g_jobcontrol.first_job->first_process->r_value = status;
	}
	else if (WIFSIGNALED(status) == TRUE)
	{
		ft_putstr("sgnal status : ");
		ft_putnbr(status);
		g_jobcontrol.first_job->first_process->status = status;
		g_jobcontrol.first_job->first_process->r_value = status + 127;
	}
	else if (WIFSTOPPED(status) == TRUE)
	{
		ft_putendl("I receive stop sig");
		//g_jobcontrol.first_job->first_process->status = g_jobcontrol.first_job->fg ? 1 : 2;
		g_jobcontrol.first_job->first_process->status = 1;
		g_jobcontrol.first_job->first_process->r_value = status;
	}
	g_jobcontrol.first_job->first_process = pro;
	return (status);
}

int		process_nb(t_process *pro)
{
	int	i;

	i = 0;
	while (pro && pro->next)
	{
		i++;
		pro = pro->next;
	}
	return (i);
}

void	wait_for_job(t_process *pro, t_job *job, int fg)
{
	pid_t	pid;
	int		status;
	t_process	*save;

	save = pro;
	pid = 0;
	if (!pro)
		return ;
	status = 0;
	signal(SIGCHLD, SIG_DFL);
	while (pro  && fg)
	{
		if (pro->lpid > 0)
			(waitpid(pro->lpid, &status, WUNTRACED));
		process_status(pro->lpid, status, pro);
		pro = pro->next;
	}
	pro = save;
	check_if_stop(pro, job);
}

t_process	*fill_jc_struc(pid_t pid, char *cmd, t_process *pro)
{
	if (!g_jobcontrol.first_job->first_process)
	{
		g_jobcontrol.first_job->first_process = ft_memalloc(sizeof(*g_jobcontrol.first_job->first_process));
		pro = g_jobcontrol.first_job->first_process;
		pro->next = NULL;
	}
	else
	{
		pro->next = ft_memalloc(sizeof(*g_jobcontrol.first_job->first_process));
		pro = pro->next;
		pro->next = NULL;
	}
	if (pid == -1)
		pro->r_value = g_jobcontrol.ret;
	pro->lpid = pid;
	pro->cmd = ft_strdup(cmd);
	if (g_jobcontrol.shell_is_int)
	{
		if (!g_jobcontrol.first_job->pgid)
		{
			if (pid > -1)
				g_jobcontrol.first_job->pgid = pid;
			else
				g_jobcontrol.first_job->pgid = g_jobcontrol.shell_pgid;
		}
		setpgid(pid, g_jobcontrol.first_job->pgid);
	}
	return (pro);
}

void	set_id_sign(int foreground)
{
	pid_t   pid;
	int		errno;
	
	errno = 0;
	pid = getpid();
	if (g_jobcontrol.first_job->pgid == 0)
       g_jobcontrol.first_job->pgid = pid;
	setpgid(pid, g_jobcontrol.first_job->pgid);
	if (foreground)
	{
		tcsetpgrp(0, g_jobcontrol.first_job->pgid);
//	ft_putendl("DAN LA COND");
	}
	ign_jb_sign(1);
}

void    fill_pipe(int oldlink[2], int newlink[2], char **av, int i)
{
    if (i > 0)
	{
        dup2(oldlink[0], 0);
		close(oldlink[0]);
	}
    if (av[i + 1])
	{
        dup2(newlink[1], 1);
		close(newlink[1]);
		close(newlink[0]);
	}
}

char	*local_file(char *str)
{
	t_read	read;
	char	*dst;

	dst = NULL;
	read.path = ft_strldup(str, '/');
	read.ptr = read.path ? opendir(read.path) : opendir(".");
	ft_strdel(&read.path);
	while (read.ptr && (read.file = readdir(read.ptr)))
	{
		read.tmp = ft_strdupn(str, '/');
		if (read.tmp && ft_strcmp(read.tmp, read.file->d_name) == 0)
		{
			dst = ft_strdup(str);
			permissions(&dst, read.rdbuf);
			ft_strdel(&read.tmp);
			break;
		}
		ft_strdel(&read.tmp);
	}
	read.ptr ? closedir(read.ptr) : 0;
	return (dst);

}

void		execute_builtin(char **cmd)
{
	if (ft_strcmp(cmd[0], "jobs") == 0)
	   	 g_jobcontrol.ret = ft_jobs(g_jobcontrol.first_mail, cmd);
	else if (ft_strcmp(cmd[0], "fg") == 0)
   		 g_jobcontrol.ret = put_in_fg(1, g_jobcontrol.first_mail, cmd);
	else if (ft_strcmp(cmd[0], "bg") == 0)
		g_jobcontrol.ret = put_in_bg(g_jobcontrol.first_mail, 1, cmd, g_jobcontrol.first_job->first_process);
	
}

char		*my_path(char **cmd, char **env)
{
	char	**tmp;
	char	*mypath;

	mypath = ft_strdup("b");
	tmp = NULL;
	if (ft_strcmp(cmd[0], "jobs") == 0 || ft_strcmp(cmd[0], "fg") == 0
		|| ft_strcmp(cmd[0], "bg") == 0)
		return (mypath);	
	else
	{
		tmp = get_line(env);
		ft_strdel(&mypath);
		if (!(mypath = local_file(cmd[0])))
		{
			mypath = get_pathh(cmd[0], tmp);
			if (!mypath)
			{
	   	 		ft_putstr_fd("Shell : No cmd found: ", 2);
				ft_putendl_fd(cmd[0], 2);
				g_jobcontrol.ret = -1;
				//g_jobcontrol.first_job->completed
			}
		}
			ft_putstr("MYPATH = ");
			ft_putendl(mypath);
	}
	ft_freetab(tmp);
	return (mypath);	
}


int		pipe_exec(char **av, char **env, int fg)
{
	int			i;
	int			ret;
	int			oldlink[2];
	int			newlink[2];
	char		*mypath;
	char    	**cmd;
	pid_t   	pid;
	t_process	*pro;

	pid = -1;
	i = 0;
	pro = NULL;
	newlink[0] = -1;
	newlink[1] = -1;
	ret = -1;
	g_jobcontrol.first_job->first_process = NULL;
	g_jobcontrol.first_job->fg = fg;
	while (av && av[i])
	{
		if (ft_strcmp(av[i], "|") == 0)
			i++;
		else
		{
			cmd = parse_redir(av[i], 0);
			oldlink[0] = newlink[0];
			if (av[i + 1] && ft_strcmp(av[i + 1], "|") == 0)
				if (pipe(newlink) < 0)
					ft_putendl_fd("Could not create the pipe", 2);
			mypath = my_path(cmd, env);
			if (ft_strcmp(mypath, "b") == 0 && !av[i + 1])
				execute_builtin(cmd);
			if (((mypath && ft_strcmp(mypath, "b")) ||  (ft_strcmp(mypath, "b") == 0 && av[i + 1] )) && (pid = fork()) == 0)
			{
//					tcsetattr(0, TCSANOW, &g_jobcontrol.first_job->j_mode);
					if (fg)
						reset_attr();
					set_id_sign(fg);
					fill_pipe(oldlink, newlink, av, i);
					parse_redir(av[i], 1);
					if (ft_strcmp(mypath, "b") == 0)
					{
						execute_builtin(cmd);
						exit(g_jobcontrol.ret);
					}
					else
					{
						execve(mypath, cmd, env);
					}
			}
//			else
//				init_shell_sig();
			if (oldlink[0] > -1)
				close (oldlink[0]);
			if (newlink[1] > -1)
				close(newlink[1]);
			ft_freetab(cmd);
			if (mypath)
				pro = fill_jc_struc(pid, av[i], pro);
			i++;
			ft_strdel(&mypath);
			pid = -1;
		}
	}
	
	if (fg)
		put_in_fg(0, g_jobcontrol.first_mail, NULL);
	else
		put_in_bg(g_jobcontrol.first_job, 0, NULL, g_jobcontrol.first_job->first_process);
//	tcgetattr(0, &g_jobcontrol.first_job->j_mode);
//	tcsetattr(0, TCSANOW, &g_jobcontrol.term_attr);
//	init_shell_sig();
	//ign_jb_sign(0);
	return (0);
}
