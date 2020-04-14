/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ari_exe_bw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 04:47:43 by geargenc          #+#    #+#             */
/*   Updated: 2020/04/14 06:21:29 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int							ft_ari_exe_bw_and(t_ari_node *node, int rec)
{
	if (g_ari_exetab[node->left->token](node->left, rec) ||
		g_ari_exetab[node->right->token](node->right, rec))
		return (-1);
	node->value = (node->left->value & node->right->value);
	return (0);
}

int							ft_ari_exe_bw_or(t_ari_node *node, int rec)
{
	if (g_ari_exetab[node->left->token](node->left, rec) ||
		g_ari_exetab[node->right->token](node->right, rec))
		return (-1);
	node->value = (node->left->value | node->right->value);
	return (0);
}

int							ft_ari_exe_bw_xor(t_ari_node *node, int rec)
{
	if (g_ari_exetab[node->left->token](node->left, rec) ||
		g_ari_exetab[node->right->token](node->right, rec))
		return (-1);
	node->value = (node->left->value ^ node->right->value);
	return (0);
}

int							ft_ari_exe_bw_not(t_ari_node *node, int rec)
{
	if (g_ari_exetab[node->right->token](node->right, rec))
		return (-1);
	node->value = (~node->right->value);
	return (0);
}
