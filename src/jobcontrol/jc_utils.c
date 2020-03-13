/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 01:28:01 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/13 01:43:40 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		process_nb(t_process *pro)
{
	int i;

	i = 0;
	while (pro && pro->next)
	{
		i++;
		pro = pro->next;
	}
	return (i);
}

void	norme(t_job *comp2, int i, t_job *save)
{
	g_jobcontrol.first_job = comp2;
	g_jobcontrol.first_job->last_j = i;
	g_jobcontrol.first_job = save;
}
