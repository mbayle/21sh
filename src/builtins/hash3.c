/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 14:54:34 by ymarcill          #+#    #+#             */
/*   Updated: 2020/04/22 14:56:04 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"
#include <sys/mman.h>
#define PATHVAR "PATH="

void				hash_reset(t_hash **hash)
{
	int				i;

	if (*hash)
	{
		i = 0;
		while (i < 256)
		{
			if ((*hash)->next[i])
				hash_reset(&((*hash)->next[i]));
			i++;
		}
		if ((*hash)->path)
			free((*hash)->path);
		free(*hash);
		*hash = NULL;
	}
}

char				*browse_command_path(char *command, char **pathlist)
{
	char			buf[PATH_MAX];
	char			*tmp;

	if (pathlist && *pathlist)
	{
		if (command && ft_strlen(*pathlist) + ft_strlen(command) + 1 < PATH_MAX)
		{
			strcpy(buf, *pathlist);
			strcat(buf, "/");
			strcat(buf, command);
			if (access(buf, X_OK) == 0)
				return ((tmp = strdup(buf)) == NULL ? MAP_FAILED : tmp);
			if (access(buf, F_OK) == 0)
				return (((tmp = browse_command_path(command, pathlist + 1)) !=
					NULL && tmp != MAP_FAILED &&
					!(tmp = strdup(buf))) ? MAP_FAILED : tmp);
		}
		return (browse_command_path(command, pathlist + 1));
	}
	return (NULL);
}

void				free_pathlist(char **pathlist)
{
	int				i;

	i = 0;
	while (pathlist[i])
	{
		free(pathlist[i]);
		i++;
	}
	free(pathlist);
}

t_hash				*browse_command(char *command, char *pathvar, t_hash **hash)
{
	t_hash			*hashhit;
	char			**pathlist;
	char			*path;

	if ((hashhit = attempt_hit(command, *hash)) &&
		access(hashhit->path, X_OK) == 0)
		return (hashhit);
	if (hashhit)
		hashhit->path = NULL;
	if (!(pathlist = getpathlist(pathvar)))
		return (MAP_FAILED);
	path = browse_command_path(command, pathlist);
	free_pathlist(pathlist);
	if (path == MAP_FAILED || path == NULL)
		return ((t_hash *)path);
	if (hashhit)
		hashhit->path = path;
	else if (!(hashhit = new_hash_entry(command, path, hash)))
		return (MAP_FAILED);
	hashhit->hits = 1;
	return (hashhit);
}

t_hash				*add_command(char *command, char *pathvar, t_hash **hash)
{
	t_hash			*hashhit;

	hashhit = browse_command(command, pathvar, hash);
	if (hashhit != MAP_FAILED && hashhit != NULL)
		hashhit->hits = 0;
	return (hashhit);
}
