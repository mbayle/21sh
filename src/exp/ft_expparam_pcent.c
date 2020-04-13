/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expparam_pcent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:09:56 by geargenc          #+#    #+#             */
/*   Updated: 2020/04/13 08:24:02 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

char			*ft_match_rmslsuffix(char *param, char *word)
{
	t_matchlist	*list;
	char		*ret;
	int			i;

	list = ft_getmatch_list(word);
	ret = NULL;
	i = 0;
	while (param[i])
		i++;
	while (!ret)
	{
		if (g_matchtab[list->token](param + i, list))
			ret = ft_strsub(param, 0, i);
		else if (!i)
			ret = ft_strdup(param);
		i--;
	}
	ft_getmatch_free(list);
	return (ret);
}

int				ft_expparam_pcent(t_txtlist *txt,
				t_expparam *expparam)
{
	char		*tmp;

	if (!expparam->param ||
		!(expparam->word = ft_simple_expanse(expparam->word)))
	{
		ft_expparam_free(expparam);
		return (ft_exp_brace_error(txt));
	}
	tmp = ft_getvar(expparam->param);
	if (!tmp)
		tmp = ft_strdup("");
	free(expparam->param);
	expparam->param = tmp;
	txt->data = ft_match_rmslsuffix(expparam->param, expparam->word);
	ft_expparam_free(expparam);
	return (0);
}

char			*ft_match_rmlgsuffix(char *param, char *word)
{
	t_matchlist	*list;
	char		*ret;
	int			i;

	list = ft_getmatch_list(word);
	ret = NULL;
	i = 0;
	while (!ret)
	{
		if (g_matchtab[list->token](param + i, list))
			ret = ft_strsub(param, 0, i);
		else if (!param[i])
			ret = ft_strdup(param);
		i++;
	}
	ft_getmatch_free(list);
	return (ret);
}

int				ft_expparam_dpcent(t_txtlist *txt,
				t_expparam *expparam)
{
	char		*tmp;

	if (!expparam->param ||
		!(expparam->word = ft_simple_expanse(expparam->word)))
	{
		ft_expparam_free(expparam);
		return (ft_exp_brace_error(txt));
	}
	tmp = ft_getvar(expparam->param);
	if (!tmp)
		tmp = ft_strdup("");
	free(expparam->param);
	expparam->param = tmp;
	txt->data = ft_match_rmlgsuffix(expparam->param, expparam->word);
	ft_expparam_free(expparam);
	return (0);
}
