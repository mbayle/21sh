/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ari_exe_others.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 05:01:39 by geargenc          #+#    #+#             */
/*   Updated: 2020/04/14 06:21:29 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int							ft_ari_exe_value(t_ari_node *node, int rec)
{
	(void)rec;
	(void)node;
	return (0);
}

int							ft_ari_exe_var(t_ari_node *node, int rec)
{
	(void)rec;
	(void)node;
	return (0);
}

int							ft_ari_exe_par_rt(t_ari_node *node, int rec)
{
	if (g_ari_exetab[node->right->token](node->right, rec))
		return (-1);
	node->value = (node->right->value);
	return (0);
}

int							ft_ari_exe_ms_sign(t_ari_node *node, int rec)
{
	if (g_ari_exetab[node->right->token](node->right, rec))
		return (-1);
	node->value = (-node->right->value);
	return (0);
}
