#include "../../includes/projectinclude.h"

char	*get_bis(t_read read, t_myenv *env)
{
	char	*dst;

	dst = NULL;
	read.path = ft_strldup(env->val, '/');
	if (read.path && (read.ptr = opendir(read.path)))
	{
		read.tmp = ft_strdupn(env->val, '/');
		while (read.ptr && (read.file = readdir(read.ptr)))
		{
			if (read.tmp && ft_strcmp(read.tmp, read.file->d_name) == 0)
			{
				dst = "yes";
				break ;
			}
		}
		ft_strdel(&read.tmp);
		ft_strdel(&read.path);
		closedir(read.ptr);
		return (dst);
	}
	ft_strdel(&read.path);
	return (NULL);
}

char	*get_myenv(char *key)
{
	t_myenv	*env;
	t_read	read;
	char	*dst;

	dst = NULL;
	env = g_jobcontrol.myenv;
	ft_bzero(&read, sizeof(read));
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			dst = get_bis(read, env);
			if (!dst)
				return (NULL);
			return (ft_strdup(env->val));
		}
		env = env->next;
	}
	return (NULL);
}

int		myenv(void)
{
	t_myenv *env;

	env = g_jobcontrol.myenv;
	while (env)
	{
		ft_putendl(env->keyval);
		env = env->next;
	}
	return (0);
}
