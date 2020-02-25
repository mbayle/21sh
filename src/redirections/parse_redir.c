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

void	parse_redir(char *line)
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
		return ;
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
				return ;
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
				return ;
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
	(void)dst;
	ft_putnbr(y);
	command[y] = NULL;
	i = 0;
	ft_putstr("MY TAB :\n");
	while (command[i])
		ft_putendl(command[i++]);
/*		if (line[i] == ' ')
		{
			command[y][x] = '\0';
			x = 0;
			command[++y] = ft_strdup("|");
			command[++y] = malloc(sizeof(char) * (ft_strlen(line) + 1));
		}
		else if (line[i])
			command[y][x++] = line[i];
	}
	command[y][x] = '\0';
	command[++y] = NULL;
	return (command);*/
}
