#include "../../includes/projectinclude.h"

char	*get_keyval_loc(char *key)
{
	t_myloc	*loc;

	loc = g_jobcontrol.myloc;
	while (loc)
	{
		if (!ft_strcmp(loc->key, key))
			return (ft_strdup(loc->keyval));
		loc = loc->next;
	}
	return (NULL);
}

int		do_setenv(char *keyval)
{
	int	ret;

	ret = 0;
	if (check_error(keyval))
		return (1);
	if (!check_loc(keyval))
	{
		ret = replace_loc(keyval);
	}
	else
	{
		ret = add_loc(keyval);
	}
	if (!check_env(keyval))
	{
		ret = replace_env(keyval, 0);
	}
	else
	{
		ret = add_env(keyval, 0);
	}
	return (ret);
}

int		myexport(char **cmd)
{
	int		i;
	int		ret;
	char	*keyval;

	i = 1;
	ret = 0;
	while (cmd[i])
	{
		if (!ft_occur(cmd[i], '='))
		{
			if (!(keyval = get_keyval_loc(cmd[i])))
			{
				ft_putendl_fd("Export: key isn't a local var", 2);
				return (1);
			}
		}
		else
			keyval = ft_strdup(cmd[i]);
		ret = do_setenv(keyval);
		ft_strdel(&keyval);
		if (ret)
			return (ret);
		i++;
	}
	return (ret);
}
