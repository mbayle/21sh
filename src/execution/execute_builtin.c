/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 20:28:20 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/12 22:59:53 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

void	exec_b(char **cmd)
{
	
	if (ft_strcmp(cmd[0], "test") == 0)
		g_jobcontrol.ret = ft_test(cmd, 0, NULL);
	if (ft_strcmp(cmd[0], "echo") == 0)
		g_jobcontrol.ret = exec_echo(cmd);
	if (ft_strcmp(cmd[0], "export") == 0)
		g_jobcontrol.ret = exec_export(&g_jobcontrol.s, cmd);
	if (ft_strcmp(cmd[0], "alias") == 0)
		g_jobcontrol.ret = exec_alias(cmd);
//  if (ft_strcmp(cmd[0], "cd") == 0)
//      g_jobcontrol.ret = fonction val;
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

int		execute_builtin(char **cmd)
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
	if (ft_strcmp(cmd[0], "setclr") == 0)
		g_jobcontrol.ret = exec_setclr(&g_jobcontrol.s, 1);
	exec_b(cmd);
	ft_strdel(&tmp);
	return (0);
}
