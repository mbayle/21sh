/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_nbr_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 23:41:53 by frameton          #+#    #+#             */
/*   Updated: 2020/03/03 22:09:01 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int			last_command(char **line, char **tmp, t_struct *s, int c)
{
	t_htr	*t;
	char	*new;

	(void)c;
	t = s->h;
	if (!s->h)
	{
		fp("fp", NULL);
		ft_2putstr("\n", RED"\"!!\": No command found."WHITE);
		return (-1);
	}
	**tmp = '\0';
	(*tmp)++;
	(*tmp)++;
	new = ft_strjoin(t->name, *tmp);
	*tmp = *line;
	*line = ft_strjoin(*line, new);
	sec_free(tmp, 0);
	sec_free(&new, 0);
	*tmp = *line;
	return (1);
}

int			no_match_cmd(t_struct *s)
{
	free_lst(s);
	fp("bl", NULL);
	ft_putchar('\n');
	ft_putstr(FRED"\"!number\": No command found."WHITE);
	return (-1);
}

static void	search_nbr_cmd2(t_htr **t, int c, int nbr)
{
	nbr = nbr * -1;
	while (*t && c != nbr)
	{
		++c;
		*t = (*t)->next;
	}
}

static int	search_nbr_cmd3(char **tmp, char **line, t_htr **t)
{
	char	*l;

	l = NULL;
	**tmp = '\0';
	(*tmp)++;
	if (**tmp == '-')
		(*tmp)++;
	while (ft_isnum(**tmp))
		(*tmp)++;
	l = ft_strjoin((*t)->name, *tmp);
	*tmp = *line;
	*line = ft_strjoin(*line, l);
	sec_free(tmp, 0);
	sec_free(&l, 0);
	*tmp = *line;
	return (1);
}

int			search_nbr_cmd(t_struct *s, char **line, char **tmp, int c)
{
	int		nbr;
	t_htr	*t;
	char	*l;

	t = s->h;
	l = *tmp;
	l++;
	if (*l == '-' && (!*(l + 1) || !ft_isnum(*(l + 1))))
		return (no_match_cmd(s));
	nbr = ft_atoi(l);
	if (nbr == 0)
		return (no_match_cmd(s));
	if (nbr > 0)
	{
		while (t->next)
			t = t->next;
		while (t && c < nbr && (c = c + 1))
			t = t->prev;
	}
	else
		search_nbr_cmd2(&t, c, nbr);
	if (!t)
		return (no_match_cmd(s));
	return (search_nbr_cmd3(tmp, line, &t));
}
