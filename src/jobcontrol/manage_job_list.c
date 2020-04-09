/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_job_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 00:30:39 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/12 20:35:13 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

void	delete_process(t_process *pro)
{
	if (!pro)
		return ;
	if (pro && pro->next)
		delete_process(pro->next);
	ft_strdel(&pro->cmd);
	ft_memdel((void**)&pro);
//	printf("%s %p\n", "adreess de pro delete_prp", pro);
}

void	delete_job(t_job *job)
{
	if (!job)
		return ;
	if (job->next)
		delete_job(job->next);
	delete_process(job->first_process);
	ft_strdel(&job->command);
	if (job->pgid != -1 && job->pgid != 0)
		kill(-(job->pgid), 9);
	ft_memdel((void**)&job);
}

t_job	*delete_first(t_job *first)
{
	t_job	*tmp;

	delete_process(first->first_process);
	ft_strdel(&first->command);
	tmp = first;
	first = first->next;
	ft_memdel((void**)&tmp);
//	printf("%s %p\n", "addr tmp dlete first", tmp);
//	printf("%s %p\n", "addr first dlete first", first);
//	if (first)
//		ft_putendl(first->command);
//	ft_memdel((void**)&g_jobcontrol.first_mail);
	if (first)
		g_jobcontrol.first_mail = first;
	else
	{
		g_jobcontrol.first_job = NULL;
		g_jobcontrol.first_mail = NULL;
	}
	return (first);
}

t_job	*delete_link(pid_t pgid)
{
	t_job	*first;
	t_job	*tmp;
	t_job	*save;

//	ft_putendl("\n\nI DELETE LINK\n\n");
	first = g_jobcontrol.first_mail;
	save = first;
	if (save && first->pgid == pgid )
		return (delete_first(first));
//	ft_putendl("NO THE FISRT");
	while (first && first->next)
	{
//			ft_putendl(first->command);
		if (first->next->pgid == pgid)
		{
//			ft_putendl("------");
//			ft_putendl(first->next->command);
//			ft_putendl("------");
			save = first;
			ft_strdel(&first->next->command);
			delete_process(first->next->first_process);
			tmp = first->next;
			if (first->next->next == NULL)
				g_jobcontrol.first_job = first;
			first->next = first->next->next;
			ft_memdel((void**)&tmp);
//		printf("%s %p\n", "addr tmp deletelink", tmp);
			break ;
		}
		first = first->next;
	}
	if (first->next)
		return (first->next);
	else 
		return (first);
}
