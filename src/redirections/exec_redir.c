/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 00:01:03 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/08 23:59:23 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int		myheredoc(char *redir, char *file, int nb)
{
	int		n;
//	int		fd;
	int		link[2];
	char	*tmp;

	link[0] = -1;
	link[1] = -1;
	ft_putendl("I do HEREDOC");
	n = dig_to_io(redir);
	ft_putnbr(n);
	if (pipe(link) < 0)
	{
		write(2, "Shell: pipe error", 17);
		return (-1);
	}
	if (check_fd(0, n))
		return (-1);
	tmp = heredoc(file);
	//fd = open("/tmp/.mytesthi", O_CREAT | O_WRONLY, 0644);
	//close(g_jobcontrol.stdi);
	if (write(link[1], tmp, (ft_strlen(tmp))) < 0)
	{
		ft_strdel(&tmp);
		write(2, "Shell: write error", 18);
		return (-1);
	}
	close(link[1]);
//	close(fd);
//	ft_putstr("MY LINE: ");
//	ft_putendl(tmp);
//	fd = open("/tmp/.mytesthi", O_CREAT | O_RDONLY, 0644);
	ft_strdel(&tmp);
	if (isatty(0) == 0)
		ft_putendl("NO TTY BEFORE DUP");
//	unlink("/tmp/.mytesthi");
	int fd;

	fd = dup(0);
	if (nb == g_jobcontrol.here)
	{
		if (dup2(link[0], n) < 0)
		{
			write(2, "Shell: bad fd", 14);
			return (-1);
		}
		close(link[0]);
	}
	if (isatty(0) == 0)
		ft_putendl("NO TTY AFTER DUP");
	return (0);
}

int		dup_fd(char *redir, char *file)
{
	int n;

	n = dig_to_io(redir);
	if (n == 0)
		n = redir[0] == '>' ? 1 : 0;
	if (!ft_strcmp(file, "-"))
		close(n);
	else if (is_strdigit(file))
	{
		if ((if_digit(file, n)) == -1)
			return (-1);
	}
	else
	{
		ft_putendl_fd("Shell: ambiguous redirect", 2);
		return (-1);
	}
	return (0);
}

int		out_err_redir(char *file)
{
	int fd;

	fd = 0;
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
			write(2, "Failure : error while creating the file", 39);
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
	if (ft_seq_occur(cmd[i], "&>"))
		ret = out_err_redir(cmd[i + 1]);
	else if (ft_seq_occur(cmd[i], ">"))
		ret = redirect_to_file(cmd[i], cmd[i + 1], O_TRUNC, 1);
	return (ret);
}

void	nb_heredoc(char **cmd)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (cmd[i])
	{
		if (ft_seq_occur(cmd[i], "<<"))
			nb++;
		i++;
	}
	g_jobcontrol.here = nb;
}

int		execute_redir(char **cmd)
{
	int i;
	int ret;
	int	nb;

	i = -1;
	ret = 0;
	nb = 0;
	g_jobcontrol.here = 0;
	nb_heredoc(cmd);
	while (cmd[++i])
	{
		if (ft_seq_occur(cmd[i], ">>"))
			ret = redirect_to_file(cmd[i], cmd[i + 1], O_APPEND, 1);
		else if (ft_seq_occur(cmd[i], "<<"))
		{
			nb++;
		//  ft_putendl("O \"<<\" has occur");
			ret = myheredoc(cmd[i], cmd[i + 1], nb);
		}
		else if (ft_seq_occur(cmd[i], ">&"))
			ret = dup_fd(cmd[i], cmd[i + 1]);
		else if (ft_seq_occur(cmd[i], "&>") || ft_seq_occur(cmd[i], ">"))
			ret = redir_to_file(cmd, i, ret);
		else if (ft_seq_occur(cmd[i], "<&"))
			ret = dup_fd(cmd[i], cmd[i + 1]);
		else if (ft_seq_occur(cmd[i], "<"))
			ret = redirect_to_file(cmd[i], cmd[i + 1], O_RDONLY, 0);
		if (ret == -1 && (g_jobcontrol.ret = 1) == 1)
			return (g_jobcontrol.red = -1);
	}
	return (0);
}
