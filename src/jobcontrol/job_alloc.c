/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 21:02:06 by ymarcill          #+#    #+#             */
/*   Updated: 2020/02/19 17:08:31 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "projectinclude.h"

char    **quick_tab_cmd(char *line)
{
		char    **command;
		int     i;
		int     x;
		int     y;

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


void    allocate_job_loop(int repere)
{
		if (!g_jobcontrol.first_job)
		{
				ft_putendl("FIRST JOB BABY");
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

