/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_cmdsub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:28:06 by geargenc          #+#    #+#             */
/*   Updated: 2020/04/29 10:20:20 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int			ft_exp_sub(t_txtlist *txt)
{
	char	*exp;

	txt->data = ft_strsub(txt->data, txt->start + 2, txt->len - 3);
	if (!(exp = ft_simple_expanse_free(txt->data)))
		return (-1);
	txt->data = (char *)ft_malloc_exit((ft_strlen(exp) + 4) * sizeof(char));
	ft_strcpy(txt->data, "$(");
	ft_strcat(txt->data, exp);
	ft_strcat(txt->data, ")");
	free(exp);
	return (0);
}
