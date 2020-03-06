/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 23:48:48 by frameton          #+#    #+#             */
/*   Updated: 2020/03/06 01:38:39 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

static int	file_history(t_htr *h, t_htr **del, t_struct *s, int fd)
{
	t_htr	*tmp;
	char	c;

	if (h)
	{
		if ((fd = open("./.history", O_WRONLY)) == -1)
			return (0);
		c = s->cpt + 48;
		write(fd, &c, 1);
		write(fd, "\n", 1);
		while (h)
		{
			write(fd, h->name, ft_strlen(h->name));
			write(fd, "\n", 1);
			h = h->next;
		}
		close(fd);
	}
	while ((tmp = *del))
	{
		(*del) = (*del)->next;
		free(tmp->name);
		free(tmp);
	}
	return (1);
}

static void	ft_exit3(t_struct *s)
{
	t_lst2	*del;

	del = NULL;
	while ((del = (*s).env))
	{
		(*s).env = (*s).env->next;
		free(del->env);
		free(del->varn);
		free(del->var);
		free(del);
	}
	free((*s).env_path);
	free_dchar(&(*s).builtin_ref);
	free_dchar(&(*s).av);
}

static void	ft_exit2(int i, t_struct *s)
{
	t_lst	*del;

	if (i == 0)
	{
		while ((del = (*s).lbg))
		{
			(*s).lbg = (*s).lbg->next;
			free(del);
		}
		file_history(s->h, &s->h, s, 0);
		ft_exit3(&*s);
		if (!(*s).exit)
			ft_eputstr(FRED"Stop: unknown error.\n"WHITE);
		exit(0);
	}
}

void		ft_exit(int i, t_struct *s)
{
	(*s).prompt = 1;
	if (i == -1)
		ft_eputstr("System opendir call failed.\n");
	ft_exit2(i, &*s);
	if (i == 1)
	{
		if (ft_strcmp((*s).av[0], " ") == 0)
			(*s).prompt = 0;
		else
			ft_2eputendl("minishell: command not found: ", s->av[0]);
	}
	if (i == -3)
		ft_2eputendl("minishell: permission denied: ", (*s).av[0]);
	if (i == -4)
		ft_2eputendl("minishell: it's a directory: ", (*s).av[0]);
	if (i == 2)
		ft_eputstr("System fork call failed.\n");
	if (i == 5)
	{
		ft_putchar('\n');
		if (!(file_history(s->h, &s->h, s, 0)))
			ft_exit2(0, s);
		exit(0);
	}
}
