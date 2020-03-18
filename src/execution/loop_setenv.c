#include "../../includes/projectinclude.h"

char	**arg_setenv(char **cmd, int pos)
{
	char	**tmp;
	
	if (!(tmp = malloc(sizeof(char *) * (tab_size(cmd) + 1))))
		return (NULL);


}

void	loop_setenv(char **cmd, int set)
{
	int		i;
	char	**tmp;

	i = set;
	if (!(tmp = malloc(sizeof(char *) * (tab_size(cmd) + 1))))
		return ;
	while (cmd[i])
	{
		if (set == 1)
		exec_setenv(&g_jobcontrol.s, cmd, );
	}
}
