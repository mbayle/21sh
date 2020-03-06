/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 01:01:35 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 02:16:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

char	*change_string2(char *bg, char *t, char *var, int c)
{
	char	*bgn;
	char	*new;

	if ((new = (char*)malloc(sizeof(*new) * (((ft_strlen(bg)
								+ ft_strlen(var)) - c) + 1))) == NULL)
		return (NULL);
	bgn = new;
	while (*bg && bg != t)
		*new++ = *bg++;
	bg++;
	while (c--)
		bg++;
	while (var && *var)
		*new++ = *var++;
	while (*bg)
		*new++ = *bg++;
	*new = '\0';
	return (bgn);
}

int		change_string(char **bg, char *t, t_struct s, size_t c)
{
	char	*new;
	char	*del;

	t++;
	while (t[c] && t[c] != '$' && ((t[c] < 9 || t[c] > 13) && t[c] != 32))
		c++;
	while (s.env)
	{
		if (c == ft_strlen(s.env->varn) && (ft_strncmp(t, s.env->varn, c)) == 0)
		{
			t--;
			del = *bg;
			if ((new = change_string2(*bg, t, s.env->var, c)) == NULL)
				return (0);
			*bg = new;
			free(del);
			break ;
		}
		s.env = s.env->next;
	}
	if (!s.env)
		return (-1);
	return (1);
}

int		check_expansion3(char **bg, char *t)
{
	int		c;
	char	*del;

	c = 0;
	while (*t && check_whitespaces(*t))
	{
		*t = '\0';
		t++;
	}
	del = *bg;
	if (!**bg && !*t)
		*bg = NULL;
	else if ((*bg = ft_strjoin(*bg, t)) == NULL)
		return (0);
	if (del)
		free(del);
	return (1);
}

int		check_expansion2(t_struct *s, int i)
{
	char	*t;
	int		c;

	t = NULL;
	if ((*s).av[i])
		t = (*s).av[i];
	while (t && *t)
	{
		if (*t == '$' && check_whitespaces(*(t + 1)))
		{
			if ((c = change_string(&(*s).av[i], t, *s, 0)) == 0)
				return (0);
			if (c == -1)
				if (check_expansion3(&(*s).av[i], t) == 0)
					return (0);
			t = (*s).av[i];
		}
		if (t)
			t++;
	}
	return (1);
}

int		check_expansion(t_struct *s, int i, t_lst2 *env, int c)
{
	if (((*s).av[0] && (*s).av[1]) && (ft_strcmp((*s).av[0], "cd") == 0
	&& ft_strcmp((*s).av[1], "-") == 0))
	{
		while (env && (ft_strcmp(env->varn, "OLD_PWD")) != 0)
			env = env->next;
		if (env)
		{
			free((*s).av[1]);
			if (((*s).av[1] = ft_mstrcpy((*s).av[1], env->var)) == NULL)
				return (0);
		}
		else if (i == 0)
			ft_eputendl(MAGENTA"Warning"WHITE": OLD_PWD var. doesn't exist.");
	}
	if ((*s).av[i][0] && (*s).av[i][0] == '~')
		if ((c = create_path_home(&*s, NULL, i)) < 1)
		{
			if (c == 0)
				return (1);
			if (c == -1)
				return (0);
		}
	if ((check_expansion2(&*s, i)) == 0)
		return (0);
	return (1);
}
