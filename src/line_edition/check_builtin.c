/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 22:18:33 by frameton          #+#    #+#             */
/*   Updated: 2019/08/18 22:03:56 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_builtin(char *s, char **builtin, t_struct st)
{
	int		c;

	c = 0;
	while (builtin[c])
	{
		if (ft_strcmp(builtin[c], s) == 0)
			return (c + 3);
		c++;
	}
	if (!(st.env_path) && st.av[0] && st.av[0][0] != '/' && st.av[0][0] != '.')
	{
		if (st.av[0][0] != ' ')
			ft_eputstr("error: the PATH environment variable doesn't exist.\n");
		return (-2);
	}
	return (0);
}
