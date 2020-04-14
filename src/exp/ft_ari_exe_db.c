/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ari_exe_db.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 04:57:17 by geargenc          #+#    #+#             */
/*   Updated: 2020/04/14 10:45:12 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int							ft_ari_exe_db_ps(t_ari_node *node, int rec)
{
	if (node->left)
	{
		if (g_ari_exetab[node->left->token](node->left, rec))
			return (-1);
		node->value = node->left->value;
		ft_ari_assign(node->left->text, node->value + 1);
	}
	else
	{
		if (g_ari_exetab[node->right->token](node->right, rec))
			return (-1);
		node->value = node->right->value + 1;
		ft_ari_assign(node->right->text, node->value);
	}
	return (0);
}

int							ft_ari_exe_db_ms(t_ari_node *node, int rec)
{
	if (node->left)
	{
		if (g_ari_exetab[node->left->token](node->left, rec))
			return (-1);
		node->value = node->left->value;
		ft_ari_assign(node->left->text, node->value - 1);
	}
	else
	{
		if (g_ari_exetab[node->right->token](node->right, rec))
			return (-1);
		node->value = node->right->value - 1;
		ft_ari_assign(node->right->text, node->value);
	}
	return (0);
}
