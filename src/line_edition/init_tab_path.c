#include "minishell.h"

static char	**create_path_tab2_b(char **path, int t)
{
	if ((path[t] = ft_mstrcpy(path[t], "./")) == NULL)
		return (NULL);
	++t;
	if ((path[t] = ft_mstrcpy(path[t], "./.builtin_name/")) == NULL)
		return (NULL);
	++t;
	path[t] = 0;
	return (path);
}

static char	**create_path_tab2(char *s, char **path)
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
	if ((path = create_path_tab2_b(path, t)) == NULL)
		return (NULL);
	return (path);
}

char		**init_tab_path2(char *s)
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
	if ((path = (char**)malloc(sizeof(*path) * (c + 3))) == NULL)
		return (NULL);
	if ((path = create_path_tab2(s, path)) == NULL)
		return (NULL);
	return (path);
}
