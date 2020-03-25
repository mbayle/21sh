/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_parse_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:43:02 by geargenc          #+#    #+#             */
/*   Updated: 2020/03/21 06:52:18 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

t_txtlist		*ft_new_txtlist(void)
{
	t_txtlist	*new;

	if (!(new = (t_txtlist *)ft_malloc_exit(sizeof(t_txtlist))))
		return (NULL);
	new->token = TXT_NONE;
	new->data = NULL;
	new->start = 0;
	new->len = 0;
	new->dquote = false;
	new->next = NULL;
	return (new);
}

t_txtlist		*ft_add_txtlist(char *data, t_txttype token, t_txtlist **to,
				bool dquote)
{
	if ((*to)->token != TXT_NONE)
	{
		if (!((*to)->next = ft_new_txtlist()))
			return (NULL);
		*to = (*to)->next;
	}
	(*to)->data = data;
	(*to)->token = token;
	(*to)->dquote = dquote;
	return (*to);
}
