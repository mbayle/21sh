/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 00:05:21 by ymarcill          #+#    #+#             */
/*   Updated: 2020/04/23 08:51:42 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int		char_pos(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int		between_q(char *str)
{
	int		i;
	int		q;
	char	c;

	i = 0;
	q = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (q == 0)
				q = 1;
			else if (c == str[i])
				q = 0;
			c = str[i];
		}
		if ((str[i] == '<' || str[i] == '>') && !q)
			return (1);
		i++;
	}
	return (0);
}

int		i_val(char **str, int i)
{
	int	pos;
	int	pos2;

	pos = char_pos(str[i], '<');
	pos2 = char_pos(str[i], '>');
	if (str[i] && (ft_occur(str[i], '<') || ft_occur(str[i], '>')))
	{
		if ((pos > 0 && str[i][pos - 1] == 92) ||
		(pos2 > 0 && str[i][pos2 - 1] == 92) || !between_q(str[i]) ||
		 ft_occur(str[i], '$'))
			return (-1);
		else if ((ft_occur(str[i], '<')) || (ft_occur(str[i], '>')))
		{
			if (str[i + 1])
				i += 2;
			else
				i++;
			return (i);
		}
	}
	return (i);
}

char	**dst_redir(char **command)
{
	int		i;
	int		y;
	int		t;
	char	**dst;

	i = 0;
	y = 0;
	t = 0;
	if (!(dst = malloc(sizeof(char *) * (tab_size(command) + 1))))
		malloc_exit();
	while (command && command[i])
	{
		t = i_val(command, i);
		if (t != -1)
			i = t;
		if (((command[i] && !ft_occur(command[i], '<') &&
		!ft_occur(command[i], '>') && (t = 0) == 0)) || t == -1)
			dst[y++] = ft_strdup(command[i++]);
	}
	dst[y] = NULL;
	return (dst);
}

char	**parse_redir(char **line, int exec)
{
	char	**dst;

	dst = dst_redir(line);
	if (exec)
	{
		execute_redir(line);
		ft_freetab(dst);
		return (NULL);
	}
	return (dst);
}
