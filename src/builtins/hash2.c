/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 14:48:48 by ymarcill          #+#    #+#             */
/*   Updated: 2020/04/22 15:08:34 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"
#include <sys/mman.h>
#define PATHVAR "PATH="

char				*getpathvar(char **envp)
{
	while (*envp)
	{
		if (strncmp(*envp, PATHVAR, strlen(PATHVAR)) == 0)
			return ((*envp) + strlen(PATHVAR));
		envp++;
	}
	return (NULL);
}

char				**getpathlist(char *pathvar)
{
	char			**pathlist;
	char			*tmp;
	int				i;

	tmp = pathvar;
	i = 0;
	while (tmp && (tmp = strchr(tmp, ':')) && (i += 1) > 0)
		tmp++;
	if (!pathvar || !(pathlist = (char **)malloc((i + 2) * sizeof(char *))))
		return (NULL);
	tmp = pathvar;
	i = 0;
	while (tmp && (tmp = strchr(tmp, ':')))
	{
		if (!(pathlist[i] = strndup(pathvar, tmp - pathvar)))
			return (NULL);
		pathvar = ++tmp;
		i++;
	}
	if (!pathvar || !(pathlist[i] = ft_strdup(pathvar)))
		return (NULL);
	pathlist[i + 1] = NULL;
	return (pathlist);
}

t_hash				*attempt_hit(char *command, t_hash *hash)
{
	if (*command && hash)
		return (attempt_hit(command + 1, hash->next[(int)*command]));
	if (hash && hash->path)
	{
		hash->hits++;
		return (hash);
	}
	return (NULL);
}

t_hash				*new_hash_page(void)
{
	t_hash			*new;

	if (!(new = (t_hash *)malloc(sizeof(t_hash))))
		return (NULL);
	bzero(new, sizeof(t_hash));
	return (new);
}

t_hash				*new_hash_entry(char *command, char *path, t_hash **hash)
{
	if (!*hash && !(*hash = new_hash_page()))
		return (NULL);
	if (*command)
	{
		return (new_hash_entry(command + 1,
		path, &((*hash)->next[(int)*command])));
	}
	(*hash)->path = path;
	(*hash)->hits = 1;
	return (*hash);
}
