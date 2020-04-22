/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 23:54:27 by ymarcill          #+#    #+#             */
/*   Updated: 2020/04/22 14:59:29 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"
#include <sys/mman.h>
#define PATHVAR "PATH="

int					exec_hash(t_hash **hash, char *pathvar, char **cmd)
{
	int				r_opt;
	int				i;

	r_opt = 0;
	while (*cmd && (*cmd)[0] == '-' && strcmp(*cmd, "--"))
	{
		i = 1;
		while ((*cmd)[i])
		{
			if ((*cmd)[i] == 'r')
				r_opt = 1;
			else
				return (hash_invalid_opt((*cmd)[i]));
			i++;
		}
		cmd++;
	}
	if ((*cmd) && (*cmd)[0] == '-')
		cmd++;
	if (r_opt)
		hash_reset(hash);
	if (*cmd)
		return (hash_add(hash, pathvar, cmd));
	print_hash(*hash);
	return (0);
}
