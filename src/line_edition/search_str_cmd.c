/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_str_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 23:42:26 by frameton          #+#    #+#             */
/*   Updated: 2020/02/22 22:43:24 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

static int	no_match_cmd_str(t_struct *s)
{
	free_lst(s);
	fp("bl", NULL);
	ft_putchar('\n');
	ft_putstr(FRED"\"!...\": No command found."WHITE);
	return (-1);
}

static int	search_str_cmd2(char **tmp, char **line, t_htr **t, int c)
{
	char	*l;

	c++;
	l = NULL;
	**tmp = '\0';
	while (c--)
		(*tmp)++;
	l = ft_strjoin((*t)->name, *tmp);
	*tmp = *line;
	*line = ft_strjoin(*line, l);
	sec_free(tmp, 0);
	sec_free(&l, 0);
	*tmp = *line;
	return (1);
}

int			search_str_cmd(t_struct *s, char **line, char **tmp, int c)
{
	char	*l;
	t_htr	*t;

	l = *tmp;
	t = s->h;
	l++;
	while (*l && !check_whitespaces(*l) && *l != '!' && (c = c + 1))
		l++;
	l = *tmp;
	l++;
	while (t)
	{
		if (!ft_strncmp(l, t->name, c))
			break ;
		t = t->next;
	}
	if (!t)
		return (no_match_cmd_str(s));
	search_str_cmd2(tmp, line, &t, c);
	return (1);
}
