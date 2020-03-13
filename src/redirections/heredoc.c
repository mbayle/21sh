/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 10:59:34 by frameton          #+#    #+#             */
/*   Updated: 2020/03/13 01:18:42 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

void	free_fornorme(int i, t_coord *c, char **arg_tab)
{
	char		*tmp2;
	static int	check = 0;

	(void)arg_tab;
	if (i == 0)
	{
		if (c->buf)
			ft_strdel(&c->buf);
		if (c->coord)
			free(c->coord);
	}
	else if (i == 1)
	{
		if (c->i > check)
		{
			tmp2 = ft_strdup(g_mainline);
			check = c->i;
		}
		else
			tmp2 = ft_strjoin(c->tmp, g_mainline);
		free(c->tmp);
		c->tmp = ft_strjoin(tmp2, "\n");
		free(tmp2);
	}
}

int		entry_h(t_coord *c, char *delim)
{
	c->mainindex = 0;
	ft_putstr_fd("\n", 0);
	c->r = c->r + get_nb_line_quote(g_mainline);
	c->t = c->r;
	if (c->coord[0] >= c->prompt[0] && c->coord[0] < c->prompt[0] + c->r)
		c->t = c->coord[0] - c->prompt[0];
	while (c->t++ < c->r)
		ft_putstr_fd("\e[B", 0);
	if (ft_strcmp(g_mainline, delim) == 0)
	{
		free(c->coord);
		free(c->prompt);
		free(c->pos);
		free(c->buf);
		return (0);
	}
	else
	{
		free_fornorme(1, c, NULL);
		ft_putstr_fd("> ", 2);
	}
	return (-1);
}

int		init_h(t_coord *c)
{
	int	a;

	a = 9;
	ft_bzero(c, sizeof(c));
	c->tmp = ft_strnew(1);
	free(g_mainline);
	g_mainline = ft_strnew(1);
	c->i = 0;
	c->k = 5;
	ft_putstr_fd("> ", 2);
	c->mainindex = 0;
	c->prompt = get_coord(get_cursor_position());
	if (c->prompt == NULL)
	{
		ft_putendl_fd("in init", 2);
		while (a--)
			ft_putchar_fd('\b', 0);
		ft_putstr_fd("\e[2K", 2);
		return (-1);
	}
	return (0);
}

int		hist_entry(t_coord *c, char *delim)
{
	if (c->buf[0] == '\n')
	{
		if (entry_h(c, delim) == 0)
		{
			ft_strdel(&g_mainline);
			return (0);
		}
		ft_strdel(&g_mainline);
		g_mainline = ft_strnew(1);
	}
	return (1);
}

char	*heredoc(char *delim)
{
	t_coord	c;

	if (init_h(&c) == -1)
		return (c.tmp);
	c.pos = NULL;
	while (42)
	{
		if ((c.buf = read_quit(&c.prompt, &c.pos, 'h')) == NULL)
			return (c.tmp);
		c.coord = get_coord(get_cursor_position());
		if (control_c(c.buf, c.prompt, c.coord, 0) == 0)
			return (c.tmp);
		c.prompt[0] = c.coord[0] == 1 ? 1 : c.prompt[0];
		c.r = main_core(c.buf, &c.prompt, &c.pos, &c.mainindex);
		if (hist_entry(&c, delim) == 0)
			return (c.tmp);
		free_fornorme(0, &c, NULL);
	}
}
