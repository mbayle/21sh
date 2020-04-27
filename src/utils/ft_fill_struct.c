/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 19:32:14 by ymarcill          #+#    #+#             */
/*   Updated: 2020/04/27 18:43:06 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		is_loc(char *keyval)
{
	t_myenv *env;

	env = g_jobcontrol.myenv;
	while (env)
	{
		if (ft_strcmp(env->keyval, keyval) == 0)
			return (0);
		env = env->next;
	}
	return (1);
}

static void	ft_fenv_free(t_struct *s)
{
	t_lst2	*del;
	t_lst2	*save;
	
	del = NULL;
	save = (*s).env;
	while ((del = (*s).env))
	{
		(*s).env = (*s).env->next;
		free(del->env);
		free(del->varn);
		free(del->var);
		free(del);
	}
	(*s).env = save;
}

void	fill_struct_env(void)
{
	t_lst2	*lst;
	t_myloc	*loc;

	ft_putendl("IM YAELLE FT");
	loc = g_jobcontrol.myloc;
	ft_fenv_free(&g_jobcontrol.s);
	g_jobcontrol.s.env = ft_memalloc(sizeof(*g_jobcontrol.s.env));
	g_jobcontrol.s.env->next = NULL;
	lst = g_jobcontrol.s.env;
	while (loc)
	{
		lst->env = ft_strdup(loc->keyval);
		lst->varn = ft_strdup(loc->key);
		lst->var = ft_strdup(loc->val);
		lst->lcl = 0;
		if (is_loc(loc->keyval))
			lst->lcl = 1;
		if (loc->next)
		{
			lst->next = ft_memalloc(sizeof(*g_jobcontrol.s.env));
			lst->next->next = NULL;
			lst = lst->next;
		}
		loc = loc->next;
	}
}
