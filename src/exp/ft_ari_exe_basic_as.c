/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ari_exe_basic_as.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 04:55:16 by geargenc          #+#    #+#             */
/*   Updated: 2020/04/14 10:33:46 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int							ft_ari_exe_ps_as(t_ari_node *node, int rec)
{
	if (ft_ari_exe_ps(node, rec))
		return (-1);
	ft_ari_assign(node->left->text, node->value);
	return (0);
}

int							ft_ari_exe_ms_as(t_ari_node *node, int rec)
{
	if (ft_ari_exe_ms(node, rec))
		return (-1);
	ft_ari_assign(node->left->text, node->value);
	return (0);
}

int							ft_ari_exe_mul_as(t_ari_node *node, int rec)
{
	if (ft_ari_exe_mul(node, rec))
		return (-1);
	ft_ari_assign(node->left->text, node->value);
	return (0);
}

int							ft_ari_exe_div_as(t_ari_node *node, int rec)
{
	if (ft_ari_exe_div(node, rec))
		return (-1);
	ft_ari_assign(node->left->text, node->value);
	return (0);
}

int							ft_ari_exe_mod_as(t_ari_node *node, int rec)
{
	if (ft_ari_exe_mod(node, rec))
		return (-1);
	ft_ari_assign(node->left->text, node->value);
	return (0);
}
