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
	t_index	index;
	char    **command;

	ft_bzero(&index, sizeof(index));
	if (!line || !(command = malloc(sizeof(char*) * (ft_occur(line, '|') * 2 +
	2))) || !(command[index.y] = malloc(sizeof(char) * (ft_strlen(line) + 1))))
		return (NULL);
	while (line[index.i])
	{
		if (line[index.i] == '|')
		{
			command[index.y][index.x] = '\0';
			index.x = 0;
			command[++index.y] = ft_strdup("|");
			if (!(command[++index.y] = malloc(sizeof(char) *
			(ft_strlen(line) + 1))))
				return (NULL);
		}
		else
			command[index.y][index.x++] = line[index.i];
		index.i++;
	}
	command[index.y][index.x] = '\0';
	command[++index.y] = NULL;
	return (command);
}


void    allocate_job_loop(int repere)
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
		g_jobcontrol.first_job->next =
				ft_memalloc(sizeof(*g_jobcontrol.first_job));
		g_jobcontrol.first_job = g_jobcontrol.first_job->next;
		g_jobcontrol.first_job->command = ft_strnew(1);
		g_jobcontrol.first_job->next = NULL;
	}
}

