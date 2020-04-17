/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_to_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 00:14:15 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/13 01:20:00 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

char		*exp_free(char *file)
{
	char	*tmp;

	tmp = ft_strdup(file);
	ft_strdel(&file);
	file = ft_simple_expanse(tmp);
	ft_strdel(&tmp);
	return (file);
}

int		write_in(int n, char *file, mode_t mode)
{
	int	fd;

	file = ft_simple_expanse(file);
	if (access(file, F_OK) == -1)
	{
		if ((fd = open(file, O_CREAT, 0644)) < 0)
		{
			ft_strdel(&file);
			ft_putendl_fd("Failure : error while creating the file", 2);
			return (-1);
		}
		close(fd);
	}
	fd = open(file, O_RDWR | mode);
	ft_strdel(&file);
	if (check_fd(fd, n))
		return (-1);
	if (dup2(fd, n) == -1)
	{
		ft_putendl_fd("Shell: Bad file descriptor", 2);
		return (-1);
	}
	return (0);
}

int		read_from(int n, char *file)
{
	int	fd;

	file = ft_simple_expanse(file);
	if (access(file, F_OK) == -1)
	{
		ft_putendl_fd("No such file or directory", 2);
		return (-1);
	}
	fd = open(file, O_RDWR);
	if (check_fd(fd, n))
		return (-1);
	if (dup2(fd, n) == -1)
	{
		ft_putendl_fd("Shell: Bad file descriptor", 2);
		return (-1);
	}
	return (0);
}

int		redirect_to_file(char *redir, char *file, mode_t mode, int stfd)
{
	int	n;

	n = dig_to_io(redir);
	if (n == 0)
		n = redir[0] == '>' ? 1 : 0;
	if (fcntl(n, F_GETFD) == -1)
	{
		ft_putendl_fd("Shell: bad fd", 2);
		return (-1);
	}
	if (stfd)
		return (write_in(n, file, mode));
	else
		return (read_from(n, file));
}
