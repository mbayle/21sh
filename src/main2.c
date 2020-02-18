/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 22:48:47 by ymarcill          #+#    #+#             */
/*   Updated: 2020/02/18 01:30:04 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <input.h>
#include <jobcontrol.h>

int		first_occur(char *str, char c)
{
	int	i = 0;

	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

char	**quick_tab_cmd(char *line)
{
	char	**command;
	int		i;
	int		x;
	int		y;

	i = -1;
	x = 0;
	y = 0;
	if (!line)
		return (NULL);
	command = malloc(sizeof(char*) * (ft_occur(line, '|') * 2 + 2));
	command[y] = malloc(sizeof(char) * (ft_strlen(line) + 1));
	while (line[++i])
	{
		if (line[i] == '|')
		{
			command[y][x] = '\0';
			x = 0;
			command[++y] = ft_strdup("|");
			command[++y] = malloc(sizeof(char) * (ft_strlen(line) + 1));
		}
		else
			command[y][x++] = line[i];
	}
	command[y][x] = '\0';
	command[++y] = NULL;
	return (command);
}

void	allocate_job_loop(int repere)
{
	if (!g_jobcontrol.first_job)
	{	
		ft_memdel((void**)g_jobcontrol.first_mail);
		g_jobcontrol.first_mail = ft_memalloc(sizeof(*g_jobcontrol.first_job));
		g_jobcontrol.first_mail->pgid = 0;
		g_jobcontrol.first_mail->last_j = 0;
		g_jobcontrol.repere = repere;
		g_jobcontrol.shell_is_int = isatty(0);
		g_jobcontrol.first_job = g_jobcontrol.first_mail;
		g_jobcontrol.first_job->command = ft_strnew(1);
		g_jobcontrol.first_job->next = NULL;
	}
	else
	{
		//ft_putendl(g_jobcontrol.first_job->command);
		g_jobcontrol.first_job->next = ft_memalloc(sizeof(*g_jobcontrol.first_job));
		g_jobcontrol.first_job = g_jobcontrol.first_job->next;
		g_jobcontrol.first_job->command = ft_strnew(1);
		g_jobcontrol.first_job->next = NULL;
	}
}

int		check_if_stp_left(int check)
{
	int 	i;
	t_job	*j;

	i = 0;
	j = g_jobcontrol.first_mail;
	if (check != 0)
		return (0);
	while (j)
	{
		if (j->stop == 1 || j->fg != 1)
			i++;
		j = j->next;
	}
	if (i > 0)
		ft_putendl_fd("There are stopped jobs", 2);
	return (i);
}

int		main(int ac,char **av, char **env)
{
	char	*line;
	char	**command;
	int		i = 0;
	int		check = 0;
	int		repere = 0;
	
	(void)ac;
	(void)av;
	line = NULL;
	init_shell_sig();
	ft_putstr_fd("Prompt> ", 2);
	g_jobcontrol.first_job = NULL;;
	g_jobcontrol.first_mail = NULL;;
	while (get_next_line(0, &line) != -1)
	{
		if (!line || line[0] == 4)
		{
			ft_putendl_fd("exit", 2);
			if (check_if_stp_left(check))
			{
				check++;
				ft_putstr_fd("Prompt> ", 2);
				continue;
			}
			break;
		}
		if (line[0] ==  3 || line[0] == '\0')
		{
			update_bg_status();
			ft_putstr_fd("Prompt> ", 2);
			continue ;
		}
		allocate_job_loop(repere);
		g_jobcontrol.first_job->command = ft_strdup(line);
		command = quick_tab_cmd(line);
		if (line[0])
		{
			ft_putendl("IN MAIN");
			pipe_exec(command, env, i);
		}
		ft_freetab(command);
		update_bg_status();
		ft_strdel(&line);
		ft_putstr_fd("Prompt> ", 2);
		i = 1;
	}
	//ft_strdel(&);
	ign_jb_sign(1);
	reset_shell_attr(0);
	delete_job(g_jobcontrol.first_mail);
	return (0);
}
