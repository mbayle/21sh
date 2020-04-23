/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_cmdsub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:28:06 by geargenc          #+#    #+#             */
/*   Updated: 2020/04/23 10:04:08 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int			ft_exp_sub(t_txtlist *txt)
{
	txt->data = ft_strsub(txt->data, txt->start + 2, txt->len - 3);
	if (!(txt->data = ft_simple_expanse_free(txt->data)))
		return (-1);
	return (0);
}
