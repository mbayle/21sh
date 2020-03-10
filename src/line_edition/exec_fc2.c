#include "../../includes/projectinclude.h"

int		eq_sign(char *str)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			flag = 1;
		i++;
	}
	return (flag);
}

char	*quote_remove(char *tmp)
{
	int		i;
	int		a;
	char	*new;

	i = 0;
	a = 0;
	if (!tmp)
		return (NULL);
	new = ft_strnew(ft_strlen(tmp) + 1);
	while (tmp[i])
	{
		if (tmp[i] != '"' && tmp[i] != '\'')
		{
			new[a] = tmp[i];
			a++;
		}
		i++;
	}
	new[a] = '\0';
	ft_strdel(&tmp);
	return (new);
}

void	get_keyval(t_fcparse *f)
{
	t_lstcontainer	*list;
	t_list			*tmp;

	list = ft_strsplitlst(f->frst, '=');
	if (!list || !list->firstelement || !list->firstelement->next)
		return ;
	ft_free(f->frst);
	tmp = list->firstelement;
	f->frst = ft_strdup(tmp->content);
	tmp = tmp->next;
	if (!tmp)
		return ;
	ft_free(f->scd);
	f->scd = ft_strdup(tmp->content);
	ft_freesplitlist(list);
}

char	*ft_swap_fc(char *tmp, t_fc *f)
{
	t_lstcontainer	*list;

	if (!tmp)
		return (NULL);
	get_keyval(f);
	if (!f->frst || !f->scd)
		return (NULL);
	tmp = quote_remove(tmp);
	if (!tmp)
		return (NULL);
	list = ft_split_with_char(tmp);
	ft_strdel(&tmp);
	if (list)
		swap_list(list, f);
	tmp = rebuild_line(list);
	return (tmp);
}

int		create_fc_oldnew(t_fc *f)
{
	int		flag;
	t_list	*tmp;
	char	*cmd;

	if (!g_tracking.mysh || !g_tracking.mysh->hist
		|| !g_tracking.mysh->hist->firstelement)
		return (-1);
	flag = 0;
	if (f->min == -4)
		flag = 1;
	get_neg_offset(f);
	tmp = ft_lstget(opt->max, g_tracking.mysh->hist->firstelement);
	cmd = ft_strdup(tmp->content);
	if (flag == 1)
	{
		if (!f->frst)
			fc_error(5, NULL);
		if (eq_sign(f->frst) > 1)
			fc_error(5, NULL);
		cmd = ft_swap_fc(cmd, f);
	}
	ft_putendl(cmd);
	main_loop(cmd);
	ft_strdel(&cmd);
	return (0);
}
