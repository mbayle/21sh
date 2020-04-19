/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 12:43:21 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/12 05:43:42 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		exec_echo(char **cmd)
{
	int	i;
	int	ret;
	int	e;

	i = 1;
	e = 0;
	ret = 0;
	if (cmd && cmd[i] && ft_strcmp(cmd[i], "-n") == 0)
		e = 1;
	while (cmd && cmd[i + e])
	{
		if (write(1, (cmd[i + e]), ft_strlen(cmd[i + e])) == -1)
			return (-1);
		if (cmd[i + e + 1] && write(1, " ", 1) == -1)
			return (-1);
		i++;
	}
	if (e == 1)
		ft_putendl("\x1b[30;47m%\x1b[0m");
	else
		ft_putchar('\n');
	return (ret);
}
