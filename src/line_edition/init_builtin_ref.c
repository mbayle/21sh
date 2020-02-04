/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtin_ref.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 22:30:09 by frameton          #+#    #+#             */
/*   Updated: 2020/02/03 23:51:13 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_builtin_ref2(int c, char **builtin)
{
	builtin[c] = ft_mstrcpy(builtin[c], "echo");
	++c;
	builtin[c] = ft_mstrcpy(builtin[c], "cd");
	++c;
	builtin[c] = ft_mstrcpy(builtin[c], "setenv");
	++c;
	builtin[c] = ft_mstrcpy(builtin[c], "unsetenv");
	++c;
	builtin[c] = ft_mstrcpy(builtin[c], "env");
	++c;
	builtin[c] = ft_mstrcpy(builtin[c], "exit");
	++c;
	builtin[c] = ft_mstrcpy(builtin[c], "setcpt");
	++c;
	builtin[c] = ft_mstrcpy(builtin[c], "help");
	++c;
	builtin[c] = ft_mstrcpy(builtin[c], "history");
	++c;
	builtin[c] = 0;
	c = 0;
	return (builtin);
}

char	**init_builtin_ref(int c)
{
	char	**builtin;

	if ((builtin = (char**)malloc(sizeof(*builtin) * 10)) == NULL)
		return (NULL);
	builtin = init_builtin_ref2(c, builtin);
	while (c < 6)
	{
		if (!builtin[c])
			return (NULL);
		c++;
	}
	return (builtin);
}
