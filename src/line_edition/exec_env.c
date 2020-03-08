#include "../../includes/projectinclude.h"

int		exec_env(t_struct *s)
{
	t_lst2		*l;

	l = s->env;
	while (l)
	{
		ft_putendl(l->env);
		l = l->next;
	}
	return (0);
}
