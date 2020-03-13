/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 22:41:01 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/12 22:52:11 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		elst_size(t_lst2 *menv)
{
	int nb;

	nb = 0;
	while (menv)
	{
		nb++;
		menv = menv->next;
	}
	return (nb);
}
