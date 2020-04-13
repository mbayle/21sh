/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expparam_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:53:55 by geargenc          #+#    #+#             */
/*   Updated: 2020/04/13 08:25:37 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int				ft_expparam_cnplus(t_txtlist *txt,
				t_expparam *expparam)
{
	if (!expparam->param ||
		!(expparam->word = ft_simple_expanse(expparam->word)))
	{
		ft_expparam_free(expparam);
		return (ft_exp_brace_error(txt));
	}
	txt->data = ft_getvar(expparam->param);
	if (txt->data && !txt->data[0])
	{
		free(txt->data);
		txt->data = NULL;
	}
	if (txt->data)
	{
		free(txt->data);
		txt->data = ft_backslash_quotes(expparam->word, txt->dquote);
		expparam->word = NULL;
	}
	else
		txt->data = ft_strdup("");
	ft_expparam_free(expparam);
	return (0);
}

int				ft_expparam_plus(t_txtlist *txt,
				t_expparam *expparam)
{
	if (!expparam->param ||
		!(expparam->word = ft_simple_expanse(expparam->word)))
	{
		ft_expparam_free(expparam);
		return (ft_exp_brace_error(txt));
	}
	txt->data = ft_getvar(expparam->param);
	if (txt->data)
	{
		free(txt->data);
		txt->data = ft_backslash_quotes(expparam->word, txt->dquote);
		expparam->word = NULL;
	}
	else
		txt->data = ft_strdup("");
	ft_expparam_free(expparam);
	return (0);
}
