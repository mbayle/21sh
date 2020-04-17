/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expparam_equal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:47:58 by geargenc          #+#    #+#             */
/*   Updated: 2020/04/15 17:01:26 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

void			ft_expparam_assign(t_expparam *expparam)
{
	char		*assign;
	char		**tmp;
	size_t		param_len;

	if (!(tmp = malloc(sizeof(char*) * 2)))
		malloc_exit();
	if (ft_isalpha(expparam->param[0]) || expparam->param[0] == '_')
	{
		param_len = ft_strlen(expparam->param);
		assign = (char *)ft_malloc_exit((param_len + ft_strlen(expparam->word)
			+ 2) * sizeof(char));
		ft_strcpy(assign, expparam->param);
		assign[param_len] = '=';
		ft_strcpy(assign + param_len + 1, expparam->word);
		tmp[0] = ft_strdup(assign);
		tmp[1] = NULL;
		setloc(tmp);
//		check_local_variable(shell, assign);
		free(assign);
	}
}

int				ft_expparam_cnequal(t_txtlist *txt,
				t_expparam *expparam)
{
	char		*tmp;

	if (!(tmp = expparam->param) ||
		!(expparam->word = ft_simple_expanse(expparam->word)))
	{
		ft_expparam_free(expparam);
		return (tmp ? -1 : ft_exp_brace_error(txt));
	}
	txt->data = ft_getvar(expparam->param);
	if (txt->data && !txt->data[0])
	{
		free(txt->data);
		txt->data = NULL;
	}
	if (txt->data)
		txt->data = ft_backslash_quotes(txt->data, txt->dquote);
	else
	{
		ft_expparam_assign(expparam);
		txt->data = ft_backslash_quotes(expparam->word, txt->dquote);
		expparam->word = NULL;
	}
	ft_expparam_free(expparam);
	return (0);
}

int				ft_expparam_equal(t_txtlist *txt,
				t_expparam *expparam)
{
	char		*tmp;

	if (!(tmp = expparam->param) ||
		!(expparam->word = ft_simple_expanse(expparam->word)))
	{
		ft_expparam_free(expparam);
		return (tmp ? -1 : ft_exp_brace_error(txt));
	}
	txt->data = ft_getvar(expparam->param);
	if (txt->data)
		txt->data = ft_backslash_quotes(txt->data, txt->dquote);
	else
	{
		ft_expparam_assign(expparam);
		txt->data = ft_backslash_quotes(expparam->word, txt->dquote);
		expparam->word = NULL;
	}
	ft_expparam_free(expparam);
	return (0);
}
