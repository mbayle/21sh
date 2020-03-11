/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 23:54:27 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/11 05:49:18 by ymarcill         ###   ########.fr       */
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
	while (tmp && (tmp = strchr(tmp, ':')))
	{
		tmp++;
		i++;
	}
	if (!(pathlist = (char **)malloc((i + 2) * sizeof(char *))))
		return (NULL);
	tmp = pathvar;
	i = 0;
	while (tmp && (tmp = strchr(tmp, ':')))
	{
		if (!(pathlist[i++] = strndup(pathvar, tmp - pathvar)))
			return (NULL);
		pathvar = ++tmp;
	}
	if (pathvar && !(pathlist[i] = strdup(pathvar)))
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
		return (new_hash_entry(command + 1, path,
			&((*hash)->next[(int)*command])));
		(*hash)->path = path;
	(*hash)->hits = 1;
	return (*hash);
}

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

	if (*pathlist)
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
	while(pathlist[i])
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
	free_pathlist(pathlist);;
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

void				rec_print_hash(t_hash *hash)
{
	int				i;

	if (hash->path)
		printf("%4d    %s\n", hash->hits, hash->path);
	i = 0;
	while (i < 256)
	{
		if (hash->next[i])
			rec_print_hash(hash->next[i]);
		i++;
	}
}

void				print_hash(t_hash *hash)
{
	if (hash)
	{
		printf("hits    command\n");
		rec_print_hash(hash);
	}
}

/*int					main(int argc, char **argv, char **envp)
{
	char			*pathvar;
	t_hash			*hashtable;
	t_hash			*ret;

	pathvar = getpathvar(envp);
	hashtable = NULL;
	ret = browse_command("ls", pathvar, &hashtable);
	if (ret != NULL && ret != MAP_FAILED)
		printf("%s %d\n", ret->path, ret->hits);
	hash_reset(&hashtable);
	ret = browse_command("ls", pathvar, &hashtable);
	if (ret != NULL && ret != MAP_FAILED)
		printf("%s %d\n", ret->path, ret->hits);
	print_hash(hashtable);
	ret = add_command("lulu", pathvar, &hashtable);
	if (ret != NULL && ret != MAP_FAILED)
		printf("%s %d\n", ret->path, ret->hits);
	print_hash(hashtable);
	ret = add_command("bash", pathvar, &hashtable);
	if (ret != NULL && ret != MAP_FAILED)
		printf("%s %d\n", ret->path, ret->hits);
	print_hash(hashtable);
	ret = browse_command("bash", pathvar, &hashtable);
	if (ret != NULL && ret != MAP_FAILED)
		printf("%s %d\n", ret->path, ret->hits);
	print_hash(hashtable);
	while (1);
	return (0);
}*/

int					hash_invalid_opt(char opt)
{
	printf("shell: hash: -%c: invalid option\n", opt);
	return (2);
}

int					hash_not_found(char *cmd)
{
	printf("shell: hash: %s: not found\n", cmd);
	return (1);
}

int					hash_add(t_hash **hash, char *pathvar, char **cmd)
{
	int				ret_value;
	t_hash			*ret;

	ret_value = 0;
	while (*cmd)
	{
		ret = add_command(*cmd, pathvar, hash);
		if (ret == MAP_FAILED)
			exit(2);
		if (ret == NULL)
			ret_value = hash_not_found(*cmd);
		cmd++;
	}
	return (ret_value);
}


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
