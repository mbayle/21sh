/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_path_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:57:37 by frameton          #+#    #+#             */
/*   Updated: 2020/03/03 22:09:01 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int		free_path(char ***path, int i)
{
	if (*path)
	{
		free_dchar(&*path);
		*path = NULL;
	}
	return (i);
}

int		rac_free_bcom(t_struct *s, int i)
{
	free_bcom(s);
	return (i);
}
