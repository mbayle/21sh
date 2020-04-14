/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ari_exe_pow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 05:00:11 by geargenc          #+#    #+#             */
/*   Updated: 2020/04/14 09:50:16 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int							ft_ari_negative_exponent(char *input)
{
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	ft_putstr_fd(input, STDERR_FILENO);
	ft_putstr_fd(": exponent less than 0\n", STDERR_FILENO);
	return (-1);
}

int							ft_ari_exe_pow(t_ari_node *node, int rec)
{
	long					pow;

	if (g_ari_exetab[node->left->token](node->left, rec) ||
		g_ari_exetab[node->right->token](node->right, rec))
		return (-1);
	node->value = 1;
	if ((pow = node->right->value) < 0)
		return (ft_ari_negative_exponent(node->input));
	while (pow)
	{
		node->value *= node->left->value;
		pow--;
	}
	return (0);
}
