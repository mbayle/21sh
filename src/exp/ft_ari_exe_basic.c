/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ari_exe_basic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 04:49:30 by geargenc          #+#    #+#             */
/*   Updated: 2020/04/18 18:33:14 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int							ft_ari_exe_ps(t_ari_node *node, int rec)
{
	if (g_ari_exetab[node->left->token](node->left, rec) ||
		g_ari_exetab[node->right->token](node->right, rec))
		return (-1);
	node->value = (node->left->value + node->right->value);
	return (0);
}

int							ft_ari_exe_ms(t_ari_node *node, int rec)
{
	if (g_ari_exetab[node->left->token](node->left, rec) ||
		g_ari_exetab[node->right->token](node->right, rec))
		return (-1);
	node->value = (node->left->value - node->right->value);
	return (0);
}

int							ft_ari_exe_mul(t_ari_node *node, int rec)
{
	if (g_ari_exetab[node->left->token](node->left, rec) ||
		g_ari_exetab[node->right->token](node->right, rec))
		return (-1);
	node->value = (node->left->value * node->right->value);
	return (0);
}

int							ft_ari_exe_div(t_ari_node *node, int rec)
{
	if (g_ari_exetab[node->left->token](node->left, rec) ||
		g_ari_exetab[node->right->token](node->right, rec))
		return (-1);
	if (node->right->value == 0)
		return (ft_ari_zero_divisor(node->input));
	node->value = (node->left->value / node->right->value);
	return (0);
}

int							ft_ari_exe_mod(t_ari_node *node, int rec)
{
	if (g_ari_exetab[node->left->token](node->left, rec) ||
		g_ari_exetab[node->right->token](node->right, rec))
		return (-1);
	if (node->right->value == 0)
		return (ft_ari_zero_divisor(node->input));
	node->value = (node->left->value % node->right->value);
	return (0);
}
