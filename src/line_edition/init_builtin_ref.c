/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtin_ref.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 22:30:09 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 02:16:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

char	**init_builtin_ref2(int c, char **builtin)
{
	builtin[c] = ft_strdup("echo");
	++c;
	builtin[c] = ft_strdup("cd");
	++c;
	builtin[c] = ft_strdup("setenv");
	++c;
	builtin[c] = ft_strdup("unsetenv");
	++c;
	builtin[c] = ft_strdup("env");
	++c;
	builtin[c] = ft_strdup("exit");
	++c;
	builtin[c] = ft_strdup("setcpt");
	++c;
	builtin[c] = ft_strdup("help");
	++c;
	builtin[c] = ft_strdup("history");
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
