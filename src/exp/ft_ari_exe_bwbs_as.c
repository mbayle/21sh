/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ari_exe_bwbs_as.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 04:56:08 by geargenc          #+#    #+#             */
/*   Updated: 2020/04/14 10:35:04 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int							ft_ari_exe_bw_and_as(t_ari_node *node, int rec)
{
	if (ft_ari_exe_bw_and(node, rec))
		return (-1);
	ft_ari_assign(node->left->text, node->value);
	return (0);
}

int							ft_ari_exe_bw_or_as(t_ari_node *node, int rec)
{
	if (ft_ari_exe_bw_or(node, rec))
		return (-1);
	ft_ari_assign(node->left->text, node->value);
	return (0);
}

int							ft_ari_exe_bw_xor_as(t_ari_node *node, int rec)
{
	if (ft_ari_exe_bw_xor(node, rec))
		return (-1);
	ft_ari_assign(node->left->text, node->value);
	return (0);
}

int							ft_ari_exe_bs_lt_as(t_ari_node *node, int rec)
{
	if (ft_ari_exe_bs_lt(node, rec))
		return (-1);
	ft_ari_assign(node->left->text, node->value);
	return (0);
}

int							ft_ari_exe_bs_rt_as(t_ari_node *node, int rec)
{
	if (ft_ari_exe_bs_rt(node, rec))
		return (-1);
	ft_ari_assign(node->left->text, node->value);
	return (0);
}
