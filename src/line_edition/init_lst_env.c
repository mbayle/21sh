/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 23:58:20 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 22:34:51 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

static void	init_lst_env2(t_lst2 **bg, t_lst2 **l, t_lst2 **tmp)
{
	static int	c;

	(*l)->size = ft_strlen((*l)->env);
	(*l)->nvar = ft_strlen((*l)->varn);
	(*l)->next = NULL;
	if (!c)
	{
		*tmp = *l;
		*bg = *l;
		c = 1;
	}
	else
	{
		(*tmp)->next = *l;
		*tmp = (*tmp)->next;
	}
}

static int	init_lst_env3(t_lst2 **l, t_lst2 **bg, t_lst2 **tmp, char ***env)
{
	int		lv;
	char	*tp;

	lv = 0;
	tp = NULL;
	init_lst_env2(&*bg, &*l, &*tmp);
	if (ft_strcmp("SHLVL", (*l)->varn) == 0)
	{
		lv = ft_atoi((*l)->var);
		lv++;
		free((*l)->var);
		free((*l)->env);
		if (((*l)->var = ft_itoa(lv)) == 0)
			return (0);
		if (((*l)->env = ft_strjoin((*l)->varn, "=")) == NULL)
			return (0);
		tp = (*l)->env;
		if (((*l)->env = ft_strjoin((*l)->env, (*l)->var)) == NULL)
			return (0);
		free(tp);
	}
	*l = (*l)->next;
	(*env)++;
	return (1);
}

t_lst2		*init_lst_env(t_lst2 *l, char **env, t_lst2 *tmp, int c)
{
	t_lst2		*bg;

	bg = NULL;
	while (*env && !(c = 0))
	{
		if ((l = malloc(sizeof(*l))) == NULL)
			return (NULL);
		if ((l->env = ft_mstrcpy(l->env, *env)) == NULL)
			return (NULL);
		while ((*env)[c] && (*env)[c] != '=')
			++c;
		if ((l->varn = (char*)malloc(sizeof(*l->varn) * (c + 1))) == NULL)
			return (NULL);
		c = 0;
		while (**env && **env != '=' && (l->varn[c++] = **env))
			(*env)++;
		l->varn[c] = '\0';
		(*env)++;
		l->var = NULL;
		if ((l->nenv = ft_strlen(*env)))
			if ((l->var = ft_mstrcpy(l->var, *env)) == NULL)
				return (NULL);
		init_lst_env3(&l, &bg, &tmp, &env);
	}
	return (bg);
}
