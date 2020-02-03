#include "minishell.h"

int		free_path(char ***path, int i)
{
	free_dchar(&*path);
	return (i);
}
