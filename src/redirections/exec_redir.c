/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 00:01:03 by ymarcill          #+#    #+#             */
/*   Updated: 2020/04/29 19:43:06 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int		exec_heredoc(char *redir, char *file)
{
	int		link[2];
	int		n;

	n = dig_to_io(redir);
	if (pipe(link) < 0)
	{
		write(2, "42sh: pipe error", 17);
		return (-1);
	}
	if (check_fd(0, n))
		return (-1);
	file = ft_simple_expanse(file);
	if (write(link[1], file, (ft_strlen(file))) < 0)
	{
		write(2, "42sh: write error", 18);
		return (-1);
	}
	close(link[1]);
	if (dup2(link[0], n) < 0)
	{
		write(2, "42sh: bad fd", 14);
		return (-1);
	}
	return (0);
}

int		dup_fd(char *redir, char *file)
{
	int n;

	file = ft_simple_expanse(file);
	n = dig_to_io(redir);
	if (n == 0)
		n = redir[0] == '>' ? 1 : 0;
	if (!ft_strcmp(file, "-"))
		close(n);
	else if (is_strdigit(file))
	{
		if ((if_digit(file, n)) == -1)
		{
			ft_strdel(&file);
			return (-1);
		}
	}
	else
	{
		ft_strdel(&file);
		ft_putendl_fd("42sh: ambiguous redirect", 2);
		return (-1);
	}
	ft_strdel(&file);
	return (0);
}

int		out_err_redir(char *file)
{
	int fd;

	fd = 0;
	file = ft_simple_expanse(file);
	if (!ft_strcmp(file, "-"))
	{
		if (close(1) == -1 || close(2) == -1)
			fd = -1;
		g_jobcontrol.ret = fd;
		return (fd);
	}
	if (access(file, F_OK) == -1)
	{
		if ((fd = open(file, O_CREAT, 0644)) < 0)
		{
			write(2, "42sh: Error while creating the file", 39);
			return (-1);
		}
	}
	fd = open(file, O_WRONLY | O_TRUNC);
	dup2(fd, 2);
	dup2(fd, 1);
	close(fd);
	return (0);
}

int		redir_to_file(char **cmd, int i, int ret)
{
	if (ft_seq_occur(cmd[i], "&>") && between_q(cmd[i]) && !ie(cmd[i]))
		ret = out_err_redir(cmd[i + 1]);
	else if (ft_seq_occur(cmd[i], ">") && !ft_seq_occur(cmd[i], "\\>")
	&& between_q(cmd[i]) && !ie(cmd[i]))
		ret = redirect_to_file(cmd[i], cmd[i + 1], O_TRUNC, 1);
	return (ret);
}

int		execute_redir(char **cmd)
{
	int i;
	int ret;

	i = -1;
	ret = 0;
	g_jobcontrol.here = 0;
	while (cmd[++i])
	{
		if (ft_seq_occur(cmd[i], ">>") && between_q(cmd[i]) && !ie(cmd[i]))
			ret = redirect_to_file(cmd[i], cmd[i + 1], O_APPEND, 1);
		else if (ft_seq_occur(cmd[i], "<<") && between_q(cmd[i]) && !ie(cmd[i]))
			ret = exec_heredoc(cmd[i], cmd[i + 1]);
		else if (ft_seq_occur(cmd[i], ">&") && between_q(cmd[i]) && !ie(cmd[i]))
			ret = dup_fd(cmd[i], cmd[i + 1]);
		else if (ft_seq_occur(cmd[i], "&>") || ft_seq_occur(cmd[i], ">"))
			ret = redir_to_file(cmd, i, ret);
		else if (ft_seq_occur(cmd[i], "<&") && between_q(cmd[i]) && !ie(cmd[i]))
			ret = dup_fd(cmd[i], cmd[i + 1]);
		else if (ft_seq_occur(cmd[i], "<") && !ft_seq_occur(cmd[i], "\\<")
		&& between_q(cmd[i]) && !ie(cmd[i]))
			ret = redirect_to_file(cmd[i], cmd[i + 1], O_RDONLY, 0);
		if (ret == -1 && (g_jobcontrol.ret = 1))
			return (g_jobcontrol.red = -1);
	}
	return (0);
}
