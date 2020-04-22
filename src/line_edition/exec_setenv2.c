/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setenv2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 23:01:08 by frameton          #+#    #+#             */
/*   Updated: 2020/03/10 02:52:38 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		exec_setenv_b2(char **av, int c)
{
	if (av && av[c] && av[c][0] == '=')
	{
		ft_eputstr("setenv: "RED);
		ft_eputstr(av[c]);
		ft_eputendl(WHITE": bad variable name.");
		return (1);
	}
	return (0);
}
