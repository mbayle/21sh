#include "../../includes/projectinclude.h"

int	mypwd(void)
{
	char	*pwd;

	if (!(pwd = get_myenv("PWD")))
		pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	ft_putendl(pwd);
	ft_strdel(&pwd);
	return (0);
}
