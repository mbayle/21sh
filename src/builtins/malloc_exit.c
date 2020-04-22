/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 14:43:31 by ymarcill          #+#    #+#             */
/*   Updated: 2020/04/22 14:43:34 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

void		malloc_exit(void)
{
	ft_putendl_fd("Malloc fail, leaving the shell", 2);
	exit_edl(&g_jobcontrol.s, NULL);
}
