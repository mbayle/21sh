/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_auth.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 00:25:35 by frameton          #+#    #+#             */
/*   Updated: 2019/08/21 00:43:37 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_auth(char *s)
{
	struct stat		st;

	if (lstat(s, &st) == -1)
		return (1);
	if (S_ISDIR(st.st_mode))
		return (-4);
	if (st.st_mode & S_IXUSR)
		return (2);
	else
		return (-3);
}

int		check_ls(t_struct *s)
{
	struct stat		st;
	int				n;
	char			tmp[PATH_MAX];

	if (lstat((*s).av[1], &st) == -1)
		return (0);
	if (S_ISLNK(st.st_mode))
	{
		n = readlink((*s).av[1], tmp, PATH_MAX);
		tmp[n] = '\0';
		free((*s).av[1]);
		if (((*s).av[1] = ft_mstrcpy((*s).av[1], tmp)) == NULL)
			return (0);
	}
	return (1);
}