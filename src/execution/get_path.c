/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 23:31:23 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/12 01:59:04 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int		permissions(char **str)
{
	int	i;

	i = 0;
	if (access(*str, X_OK) == -1)
	{
		ft_putstr_fd("Shell: Permission denied: ", 2);
		ft_putendl_fd(*str, 2);
		i = 1;
		ft_strdel(str);
		*str = NULL;
	}
	return (i);
}

char	*get_line(char **env)
{
	char	**tmp;
	char	*path;
	int		i;

	i = 0;
	tmp = NULL;
	path = NULL;
	while (env && env[i])
	{
		tmp = ft_strsplit(env[i], '=');
		if (tmp[0] && (ft_strcmp(tmp[0], "PATH")) == 0)
		{
			path = ft_strdup(tmp[1]);
			ft_freetab(tmp);
			break ;
		}
		i++;
		ft_freetab(tmp);
	}
	return (path);
}

char	**get_line2(char **env)
{
	char	**tmp;
	char	**path;
	int		i;

	i = 0;
	tmp = NULL;
	path = NULL;
	while (env && env[i])
	{
		tmp = ft_strsplit(env[i], '=');
		if (tmp[0] && (ft_strcmp(tmp[0], "PATH")) == 0)
		{
			path = ft_strsplit(tmp[1], ':');
			ft_freetab(tmp);
			break ;
		}
		i++;
		ft_freetab(tmp);
	}
	return (path);
}

char	*get_pathh(char *nwav, char **path)
{
	int				i;
	DIR				*ptr;
	struct dirent	*file;
	char			*command;

	i = -1;
	command = NULL;
	while (path && path[++i])
	{
		ptr = opendir(path[i]);
		while (ptr && (file = readdir(ptr)))
		{
			if (nwav && (ft_strcmp(file->d_name, nwav)) == 0)
			{
				command = ft_strjoin(path[i], "/");
				command = ft_strjoinnf(command, nwav);
				break ;
			}
		}
		ptr ? closedir(ptr) : 0;
	}
	return (command);
}
