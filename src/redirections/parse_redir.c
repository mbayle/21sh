#include "projectinclude.h"

int		size_tab(char *line)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (line && line[i])
	{
		if (line[i] !=  ' ' && line[i] != '<' && line[i] != '>' && line[i] !='&')
		{
				nb++;
			while (line[i] && line[i] !=  ' ' && line[i] != '<' && line[i] != '>' && line[i] !='&')
				i++;
			i--;
		}
		else if (line[i] == '<' || line[i] == '>' || line[i] =='&')
		{
			nb++;
			while (line[i] == '<' || line[i]== '>' || line[i] =='&')
				i++;
			i--;
		}
		i++;
	}
	return (nb);
}

int		ft_seq_occur(char *str, char *seq)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	if (!str || !seq || ft_strlen(seq) > ft_strlen(str))
		return (0);
	while (str[i])
	{
		if (str[i] == seq[y])
		{
			while (str[i] && seq[y])
			{
				if (str[i] != seq[y])
					return (0);
				i++;
				y++;
			}
			if (y == ft_strlenu(seq))
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

int		out_err_redir(char *file)
{
	int fd;

	if (!ft_strcmp(file, "-"))
	{
		fd = close(1);
		fd = close(2);
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
	dup2(fd, 1);
	dup2(1, 2);
	close(fd);
	return (0);
}

int		dig_to_io(char *str)
{
	int		i;
	char	*dst;

	i = 0;
	if (!(dst = ft_strnew(ft_strlen(str))))
		return (-1);
	ft_putendl(str);
	while (str[i] && ft_isdigit(str[i]))
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	i = ft_atoi(dst);
	ft_strdel(&dst);
	return (i);
}

int			is_strdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}



int			dup_fd(char *redir, char *file)
{
	int	fd;
	int	n;

	n = dig_to_io(redir);
	if (n == 0)
		n = redir[0] == '>' ? 1: 0;
	if (fcntl(n, F_GETFD) == -1)
	{
		ft_putendl_fd("Shell: bad fd", 2);
		return (-1);
	}
	if (!ft_strcmp(file, "-"))
		close(n);
	else if (is_strdigit(file))
	{
		fd = dig_to_io(file);
		if (fcntl(fd, F_GETFD) == -1)
		{
			ft_putendl_fd("Shell: bad fd", 2);
			return (-1);
		}
		dup2(fd, n);
	}
	else
	{
		ft_putendl_fd("Shell: ambuguous redirect", 2);
		return (-1);
	}
	return (0);

}

//int		redir_to_file()
//{
//}

int		execute_redir(char **cmd)
{
	int i;

	i = 0;
	/*if redir error stop executing or browsing (to verify)*/
	while (cmd[i])
	{
	//	ft_putstr_fd("My command is: ", 2);
	//	ft_putendl_fd(cmd[i], 2);
		if (ft_seq_occur(cmd[i], ">>"))
		{
			if (redirect_to_file(cmd[i], cmd[i + 1], O_APPEND, 1) == -1)
				return (-1);
			ft_putendl("O \">>\" has occur");
		}
		else if (ft_seq_occur(cmd[i], "<<"))
			ft_putendl("O \"<<\" has occur");
			//redirect_to_file(cmd[i + 1], O_APPEND, 1);
		else if (ft_seq_occur(cmd[i], ">&"))
		{
			if (dup_fd(cmd[i], cmd[i + 1]) == -1)
				return (-1);
			ft_putendl("O \">&\" has occur");
			ft_putendl(cmd[i]);
		}
		else if (ft_seq_occur(cmd[i], "<&"))
		{
			if (dup_fd(cmd[i], cmd[i + 1]) == -1)
				return (-1);
			ft_putendl("O \"<&\" has occur");
		}
		else if (ft_seq_occur(cmd[i], "&>"))
		{
			if (out_err_redir(cmd[i + 1]) == -1)
				return (-1);
			ft_putendl("O \"&>\" has occur");
		}
			//redirect_to_file(cmd[i + 1], O_TRUNC, 1);
		else if (ft_seq_occur(cmd[i], ">"))
		{
			if (redirect_to_file(cmd[i], cmd[i + 1], O_TRUNC, 1) == -1)
				return (-1);
			ft_putendl("O \">\" has occur");
		}
		else if (ft_seq_occur(cmd[i], "<"))
		{
			if (redirect_to_file(cmd[i], cmd[i + 1], O_RDONLY, 0) == -1)
				return (-1);
			ft_putendl("O \"<\" has occur");
		}
		i++;
	}
	return (0);
}

char	**parse_redir(char *line, int exec)
{
	char    **command;
	char	**dst;
	int     i;
	int     x;
	int     y;

	i = 0;
	x = 0;
	y = 0;
	if (!line || !(command = malloc(sizeof(char*) * (size_tab(line) + 1))))// || !(command[y] = ft_strnew(ft_strlen(av))))
		return (NULL);
//	ft_putstr("Number of line in my tab : ");
//	ft_putnbr(size_tab(line));
//	ft_putchar('\n');
//	ft_putendl(line);
	while (line && line[i])
	{
		if (line[i] !=  ' ' && line[i] != '<' && line[i] != '>' && line[i] !='&')
		{
			if (!(command[y] = ft_strnew(ft_strlen(line))))
				return (NULL);
			while (line[i] && line[i] !=  ' ') //&& line[i] != '<' && line[i] != '>' && line[i] !='&')
				command[y][x++] = line[i++];
			command[y][x] = '\0';
			x = 0;
			y++;
			i--;
		}
		else if (line[i] == '<' || line[i] == '>' || line[i] =='&')
		{
			if (!(command[y] = ft_strnew(ft_strlen(line))))
				return (NULL);;
			while (line[i] == '<' || line[i]== '>' || line[i] =='&')
			//	i++;
				command[y][x++] = line[i++];
			command[y][x] = '\0';
			x = 0;
			y++;
			i--;
		}
		i++;
	}
//	ft_putnbr(y);
	command[y] = NULL;
	i = 0;
//	ft_putstr("MY TAB :\n");
//	while (command[i])
//		ft_putendl(command[i++]);
	i = 0;
	dst = malloc(sizeof(char *) * (y + 1));
	y = 0;
	while (command[i])
	{
		if (ft_occur(command[i], '<') || ft_occur(command[i], '>'))
		{
			i++;
			i++;
		}
		else if (command[i] && !ft_occur(command[i], '<') && !ft_occur(command[i], '>') )
		{
			dst[y++] = ft_strdup(command[i]);
			i++;
		}
	}
	dst[y] = NULL;
	i = 0;
//	ft_putstr("MY DST :\n");
//	while (dst[i])
//		ft_putendl(dst[i++]);
	if (exec)
	{
		if (execute_redir(command) == -1)
			return (NULL);
	}
//	ft_putendl("\n\n");
	ft_freetab(command);
	return (dst);
}
