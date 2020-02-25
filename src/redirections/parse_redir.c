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

void	execute_redir(char **cmd)
{
	int i;

	i = 0;
	/*if redir error stop executing or browsing (to verify)*/
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], ">>") == 0)
			redirect_to_file(cmd[i + 1], O_APPEND, 1);
		else if (ft_strcmp(cmd[i], ">") == 0)
			redirect_to_file(cmd[i + 1], O_TRUNC, 1);
		i++;
	}
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
	ft_putstr("Number of line in my tab : ");
	ft_putnbr(size_tab(line));
	ft_putchar('\n');
	ft_putendl(line);
	while (line && line[i])
	{
		ft_putchar(line[i]);
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
	ft_putnbr(y);
	command[y] = NULL;
	i = 0;
	ft_putstr("MY TAB :\n");
	while (command[i])
		ft_putendl(command[i++]);
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
	ft_putstr("MY DST :\n");
	while (dst[i])
		ft_putendl(dst[i++]);
	if (exec)
	{
		execute_redir(command);
		ft_freetab(dst);
		dst = NULL;
	}
	ft_putendl("\n\n");
	ft_freetab(command);
	return (dst);
}
