/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tab_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:45:50 by frameton          #+#    #+#             */
/*   Updated: 2020/03/06 02:24:05 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

static char	*find_home_path(t_struct st)
{
	t_lst2	*env;

	env = st.env;
	while (env && ft_strcmp(env->varn, "HOME"))
		env = env->next;
	if (env)
		return (env->var);
	return (NULL);
}

static char	**create_path_tab2_b(char **path, int t, t_struct st)
{
	char	*p;

	p = find_home_path(st);
	if ((path[t] = ft_strdup("./")) == NULL)
		return (NULL);
	++t;
	if ((path[t] = ft_strjoin(p, "/.builtin_name/")) == NULL)
		return (NULL);
	++t;
	path[t] = 0;
	return (path);
}

static char	**create_path_tab2(char *s, char **path, t_struct st)
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
		if (*s)
			s++;
		c = 0;
		++t;
	}
	if ((path = create_path_tab2_b(path, t, st)) == NULL)
		return (NULL);
	return (path);
}

char		**init_tab_path2(char *s, t_struct *st)
{
	int		c;
	char	*bg;
	char	**path;

	bg = NULL;
	if (!(c = 0) && !s)
		return (NULL);
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
	if ((path = (char**)malloc(sizeof(*path) * (c + 3))) == NULL)
		return (NULL);
	if ((path = create_path_tab2(s, path, *st)) == NULL)
		return (NULL);
	return (path);
}
