/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 00:05:21 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/10 02:42:23 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

char	*for_if(char *line, int *i)
{
	int		x;
	char	*command;

	x = 0;
	if (!(command = ft_strnew(ft_strlen(line))))
		return (NULL);
	while (line && line[*i] && line[*i] != ' ')
	{
		command[x++] = line[*i];
		*i += 1;
	}
	command[x] = '\0';
	*i -= 1;
	return (command);
}

char	*for_else(char *line, int *i)
{
	int		x;
	char	*command;

	x = 0;
	if (!(command = ft_strnew(ft_strlen(line))))
		return (NULL);
	while (line[*i] == '<' || line[*i] == '>' || line[*i] == '&')
	{
		command[x++] = line[*i];
		*i += 1;
	}
	command[x] = '\0';
	*i -= 1;
	return (command);
}

char	**fill_redir_tab(char *line)
{
	int		i;
	int		y;
	char	**command;

	y = 0;
	i = 0;
	if (!line || !(command = malloc(sizeof(char*) * (size_tab(line) + 1))))
		return (NULL);
	while (line && line[i])
	{
		if (line[i] != ' ' && line[i] != '<' && line[i] != '>' &&
			line[i] != '&')
			command[y++] = for_if(line, &i);
		else if (line[i] == '<' || line[i] == '>' || line[i] == '&')
			command[y++] = for_else(line, &i);
		i++;
	}
	command[y] = NULL;
	return (command);
}

char	**dst_redir(char **command)
{
	int		i;
	int		y;
	char	**dst;

	i = 0;
	y = 0;
	if (!(dst = malloc(sizeof(char *) * (tab_size(command) + 1))))
		return (NULL);
	while (command[i])
	{
		if (ft_occur(command[i], '<') || ft_occur(command[i], '>'))
		{
			if (command[i + 1])
				i += 2;
			else
				i++;
		}
		else if (command[i] && !ft_occur(command[i], '<') &&
		!ft_occur(command[i], '>'))
			dst[y++] = ft_strdup(command[i++]);
	}
	dst[y] = NULL;
	return (dst);
}

void	ft_printtab(char **tt)
{
	int i;

	i = 0;
	while (tt[i])
	{
		ft_putendl_fd(tt[i], 2);
		i++;
	}
}

char	**parse_redir(char *line, int exec)
{
	char	**command;
	char	**dst;

	command = fill_redir_tab(line);
	//if (exec == 0)
	// EXPANSION SUR DST RETURN DST	
	dst = dst_redir(command);
	if (exec)
	{
		execute_redir(command);
			ft_freetab(dst);
			ft_freetab(command);
			return (NULL);
	}
//	ft_printtab(dst);
	ft_freetab(command);
	return (dst);
}
