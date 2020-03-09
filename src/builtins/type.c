/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 04:08:35 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/09 07:10:30 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		is_builtin(char *cmd)
{
	if (cmd && (!ft_strcmp(cmd, "jobs") || !ft_strcmp(cmd, "fg")
	|| !ft_strcmp(cmd, "bg") || !ft_strcmp(cmd, "setcpt")
	|| !ft_strcmp(cmd, "history") || !ft_strcmp(cmd, "help")
	|| !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") ||
	!ft_strcmp(cmd, "test") || !ft_strcmp(cmd, "exit") ||
	!ft_strcmp(cmd, "setenv") || !ft_strcmp(cmd, "unsetenv") ||
	!ft_strcmp(cmd, "set") || !ft_strcmp(cmd, "unset") ||
	!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "type")))
		return (0);
	else
		return (1);
}

int		print_type(char *cmd, char *path, int a)
{
	ft_putstr(cmd);
	if (a == -1)
	{
		ft_putendl_fd(" not found", 2);
		return (1);
	}
	ft_putstr(" is ");
	if (a == 0)
		ft_putendl("a shell builtin");
	else if (a == 1 && path)
		ft_putendl_fd(path, 1);
	else if (a == 2 && path)
	{
		ft_putstr("an alias for ");
		ft_putendl(path);
	}
	return (0);
}

char	*mypath(char *cmd)
{
	char    **tmp;
	char    *path;
	t_read  rd;

	tmp = NULL;
	path = NULL;
	if (cmd)
	{
		tmp = get_line(g_jobcontrol.env);
		ft_strdel(&path);
		path = get_pathh(cmd, tmp);
		if (path)
			permissions(&path, rd.rdbuf);
		else if (!path)
			return (NULL);
		ft_freetab(tmp);
	}
	return (path);
}

int		exec_type(char **arg)
{
	int		i;
	int		ret;
	char	*path;

	i = 1;
	ret = 0;
	while (arg[i])
	{
		if (is_builtin(arg[i]) == 0)
			print_type(arg[i], NULL, 0);
		//else if ((path = is_alias(arg[i])) != NULL)
		//{
		//		print_type(arg[i], path, 2);
		//		ft_strdel(&path);
		//}
		else if ((path = mypath(arg[i])) != NULL)
		{
			print_type(arg[i], path, 1);
			ft_strdel(&path);;
		}
		else
			ret = print_type(arg[i], NULL, -1);
		i++;
	}
	return (ret);
}
