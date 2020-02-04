/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_path_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:57:37 by frameton          #+#    #+#             */
/*   Updated: 2020/01/25 00:57:38 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
