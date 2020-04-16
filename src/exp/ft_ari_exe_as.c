/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ari_exe_as.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 05:00:41 by geargenc          #+#    #+#             */
/*   Updated: 2020/04/15 17:02:03 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

void						ft_ari_assign(char *varname, long value)
{
	char					*tab[2];
	char					*text_value;

	text_value = ft_lgtoa(value);
	tab[0] = (char *)ft_malloc_exit((ft_strlen(varname) +
		ft_strlen(text_value) + 1) * sizeof(char));
	ft_strcpy(tab[0], varname);
	ft_strcat(tab[0], "=");
	ft_strcat(tab[0], text_value);
	free(text_value);
	tab[1] = NULL;
	setloc(tab);
	free(tab[0]);
}

int							ft_ari_exe_as(t_ari_node *node, int rec)
{
	if (g_ari_exetab[node->right->token](node->right, rec))
		return (-1);
	node->value = (node->right->value);
	ft_ari_assign(node->left->text, node->value);
	return (0);
}
