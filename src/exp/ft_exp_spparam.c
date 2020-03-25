/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_spparam.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:57:54 by geargenc          #+#    #+#             */
/*   Updated: 2020/03/21 07:30:30 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

// char		*ft_spparam_dollar(t_42sh *shell)
// {
// 	return (ft_itoa(shell->pid));
// }

char		*ft_spparam_qmark(void)
{
	return (ft_itoa(g_jobcontrol.ret)); // Retourne la valeur de $?
}

// char		*ft_spparam_bang(t_42sh *shell)
// {
// 	if (shell->last_bg)
// 		return (ft_itoa(shell->last_bg));
// 	return (NULL);
// }

// char		*ft_spparam_zero(t_42sh *shell)
// {
// 	if (shell->args[0])
// 		return (ft_strdup(shell->args[0]));
// 	return (ft_strdup("42sh"));
// }

char		*(*ft_get_spparam(char c))(void)
{
	int		i;

	i = 0;
	while (g_spparamtab[i].c && g_spparamtab[i].c != c)
		i++;
	return (g_spparamtab[i].f);
}
