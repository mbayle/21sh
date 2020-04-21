#include "../../includes/projectinclude.h"

void	is_valid(char *str, const char *dst, DIR *ptr)
{
	struct stat buf;
	int			i;

	(void)ptr;
	i = 0;
	i = lstat(str, &buf);
	if (i != -1 && S_ISDIR(buf.st_mode))
	{
		ft_putstr_fd("42sh: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" : is a directory", 2);
		g_jobcontrol.cm = 1;
		g_jobcontrol.ret = 127;
	}
	else if (!dst && ft_occur(str, '/'))
	{
		ft_putstr_fd("42sh: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" : no such file or directory", 2);
		g_jobcontrol.cm = 1;
		g_jobcontrol.ret = 127;
	}
}

void	if_not_cmd(char *cmd)
{
	if (g_jobcontrol.cm == 1)
		return ;
	ft_putstr_fd("42sh : No cmd found: ", 2);
	ft_putendl_fd(cmd, 2);
	g_jobcontrol.ret = 127;
	g_jobcontrol.cm = 1;
}

int		check_b(char **cmd)
{
	if (cmd && cmd[0] && (!ft_strcmp(cmd[0], "jobs") || !ft_strcmp(cmd[0], "fg")
	|| !ft_strcmp(cmd[0], "bg") || !ft_strcmp(cmd[0], "setcpt")
	|| !ft_strcmp(cmd[0], "history") || !ft_strcmp(cmd[0], "help")
	|| !ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "hash") ||
	!ft_strcmp(cmd[0], "test") || !ft_strcmp(cmd[0], "exit") ||
	!ft_strcmp(cmd[0], "setenv") || !ft_strcmp(cmd[0], "unsetenv") ||
	!ft_strcmp(cmd[0], "set") || !ft_strcmp(cmd[0], "unset") ||
	!ft_strcmp(cmd[0], "export") || !ft_strcmp(cmd[0], "type") ||
	!ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "echo") ||
	!ft_strcmp(cmd[0], "setclr") || !ft_strcmp(cmd[0], "cd") ||
	!ft_strcmp(cmd[0], "pwd") || cmd[0][0] == '\r'))
		return (0);
	else
		return (1);
}

char	**set_copy(t_myloc *menv)
{
	int		i;
	char	**dst;

	i = 0;
	if (!(dst = malloc(sizeof(char*) * ((elst_size(menv) + 1)))))
		malloc_exit();
	while (menv)
	{
		dst[i++] = ft_strdup(menv->keyval);
		menv = menv->next;
	}
	dst[i] = NULL;
	return (dst);
}
