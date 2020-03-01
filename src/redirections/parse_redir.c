#include "projectinclude.h"


char	*for_if(char **command, char *line, int *i, int *y)
{
	int x;

	x = 0;
	ft_putnbr(*y);
	ft_putnbr(*i);
	ft_putnbr(ft_strlen(line));
	while (line[x])
		ft_putchar(line[x++]);;
	x = 0;
	if (!(command[*y] = ft_strnew(ft_strlen(line))))
		return (NULL);
	while (line && line[*i] && line[*i] !=  ' ') 
		command[*y][x++] = line[*i++];
	command[*y][x] = '\0';
	*y += 2;
	*i += 1;
	return (command[*y]);
}

char	*for_else(char **command, char *line, int *i, int *y)
{
	int	x;

	x = 0;
	if (!(command[*y] = ft_strnew(ft_strlen(line))))
		return (NULL);;
	while (line[*i] == '<' || line[*i]== '>' || line[*i] =='&')
		command[*y][x++] = line[*i++];
	command[*y][x] = '\0';
	*y += 1;
	*i += 1;
	return (command[*y]);
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
		if (line[i] !=  ' ' && line[i] != '<' && line[i] != '>' && line[i] !='&')
		{
				command[y] = for_if(command, line, &i, &y);
				ft_putendl(command[y]);
		}
		else if (line[i] == '<' || line[i] == '>' || line[i] =='&')
			command[y] = for_if(command, line, &i, &y);
		i++;
	}
	command[y] = NULL;
	return (command);
}

char	**dst_redir(char **command, int j)
{
	int		i;
	int		y;
	char	**dst;

	i = 0;
	y = 0;
	if (!(dst = malloc(sizeof(char *) * (j + 1))))
		return (NULL);
	while (command[i])
	{
		if (ft_occur(command[i], '<') || ft_occur(command[i], '>'))
			i += 2;
		else if (command[i] && !ft_occur(command[i], '<') && !ft_occur(command[i], '>') )
		{
			dst[y++] = ft_strdup(command[i]);
			i++;
		}
	}
	dst[y] = NULL;
	return (dst);
}

void	ft_printtab(char **tt)
{
	int i = -1;

	while (tt[++i])
		ft_putendl(tt[i]);

}

char	**parse_redir(char *line, int exec)
{
	char    **command;
	char	**dst;
	int     i;
	int     y;

	i = 0;
	y = 0;
	command = fill_redir_tab(line);
	if (command)
		ft_printtab(command);;
	dst = dst_redir(command, y);
	if (exec)
	{
		if (execute_redir(command) == -1)
			return (NULL);
	}
	ft_freetab(command);
	return (dst);
}
