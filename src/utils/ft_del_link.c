/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 19:32:31 by ymarcill          #+#    #+#             */
/*   Updated: 2020/04/22 19:32:33 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

void	delete_process(t_process *pro)
{
	t_process	*tmp;
	t_process	*tmp2;

	tmp = pro;
	ft_strdel(&pro->cmd);
	pro = pro->next;
	while (pro && pro->next)
	{
		ft_strdel(&pro->cmd);
		tmp2 = pro;
		pro = pro->next;
		ft_memdel((void**)tmp2);
	}
	ft_memdel((void**)tmp);
}
