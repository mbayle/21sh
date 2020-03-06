/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 23:48:41 by frameton          #+#    #+#             */
/*   Updated: 2020/02/17 01:46:45 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"
#include "../../libft/libft.h"

int		free_tab_path(char ***tab, int c)
{
	free_dchar(&*tab);
	return (c);
}

int		search_exec(char *s, char ***path, DIR *dir, struct dirent *dir_el)
{
	while (**path && (ft_strcmp("./.builtin_name/", **path)))
	{
		if (!(dir = opendir(**path)))
		{
			ft_eputstr("Error opendir: bad access path.\n");
			return (-1);
		}
		while ((dir_el = readdir(dir)))
			if ((ft_strcmp(s, dir_el->d_name)) == 0)
			{
				if ((closedir(dir)) == -1)
				{
					ft_eputstr("Error: failed closedir process.\n");
					return (-1);
				}
				return (1);
			}
		if ((closedir(dir)) == -1)
		{
			ft_eputstr("Error: failed closedir process.\n");
			return (-1);
		}
		(*path)++;
	}
	return (0);
}

char	**create_path_tab(char *s, char **path)
{
	int		c;
	int		t;

	c = 0;
	t = 0;
	while (*s)
	{
		while (s[c] && s[c] != ':')
			c++;
		if ((path[t] = (char*)malloc(sizeof(*path[t]) * (c + 2))) == NULL)
			return (NULL);
		path[t] = ft_strncpy(path[t], s, c);
		path[t][c] = '/';
		path[t][c + 1] = '\0';
		while (*s && *s != ':')
			s++;
		if (!(c = 0) && *s)
			s++;
		++t;
	}
	if ((path[t] = ft_mstrcpy(path[t], "./.builtin_name/")) == NULL)
		return (NULL);
	++t;
	path[t] = 0;
	return (path);
}

char	**init_tab_path(char *s)
{
	int		c;
	char	*bg;
	char	**path;

	c = 0;
	bg = NULL;
	while (*s && *s != '=')
		s++;
	s++;
	bg = s;
	while (*s)
	{
		if (*s == ':')
			c++;
		s++;
	}
	if (c || (!c && *bg))
		c++;
	s = bg;
	if ((path = (char**)malloc(sizeof(*path) * (c + 2))) == NULL)
		return (NULL);
	if ((path = create_path_tab(s, path)) == NULL)
		return (NULL);
	return (path);
}

int		check_command(char ***t, t_struct s, char *av, int c)
{
	char	**spath;
	char	**path;

	c = check_builtin((*t)[0], s.builtin_ref, s);
	if (c || c == -2)
		return (c);
	if (s.av[0] && (s.av[0][0] == '/' || s.av[0][0] == '.'))
		return (check_auth(s.av[0]));
	if (((path = init_tab_path(s.env_path)) == NULL))
		return (0);
	spath = path;
	if ((c = search_exec((*t)[0], &spath, NULL, NULL)) == -1)
		return (free_tab_path(&path, -1));
	if (!c)
		return (free_tab_path(&path, 1));
	else
	{
		if ((av = ft_strjoin(*spath, (*t)[0])) == NULL)
			return (-1);
		free((*t)[0]);
		(*t)[0] = av;
		free_dchar(&path);
	}
	return (2);
}
