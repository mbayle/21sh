/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_cmdsub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:28:06 by geargenc          #+#    #+#             */
/*   Updated: 2020/03/21 08:00:47 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

// int			ft_exp_sub(t_txtlist *txt, t_42sh *shell)
// {
// 	if (!(txt->data = ft_cmdsub(ft_strsub(txt->data, txt->start + 2,
// 		txt->len - 3), shell, txt->dquote)))
// 		return (-1);
// 	return (0);
// }

// int			ft_exp_bquote(t_txtlist *txt, t_42sh *shell)
// {
// 	if (!(txt->data = ft_cmdsub(ft_strsub(txt->data, txt->start + 1,
// 		txt->len - 2), shell, txt->dquote)))
// 		return (-1);
// 	return (0);
// }

int			ft_exp_sub(t_txtlist *txt)
{
	char	*exp;

	txt->data = ft_strsub(txt->data, txt->start + 2, txt->len - 3);
	if (!(exp = ft_simple_expanse(txt->data)))
		return (-1);
	free(txt->data);
	txt->data = exp;
	return (0);
}
