#include "projectinclude.h"

int		write_in(int n, char *file, mode_t mode)
{
	int	fd;

	if (access(file, F_OK) == -1)
	{
		if ((fd = open(file, O_CREAT, 0644)) < 0)
		{
			ft_putendl_fd("Failure : error while creating the file", 2);
			return (-1);
		}
		close(fd);
	}
	fd = open(file, O_WRONLY | mode);
	dup2(fd, n);
	return (0);
}

int		read_from(int n, char *file)
{
	int	fd;

	if (access(file, F_OK) == -1)
	{
		ft_putendl_fd("No such file or directory", 2);
		return (-1);
	}
	fd = open(file, O_RDONLY);
	dup2(fd, n);
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
