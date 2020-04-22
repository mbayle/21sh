/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 12:43:21 by ymarcill          #+#    #+#             */
/*   Updated: 2020/04/22 14:45:30 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		echo_error(void)
{
	ft_putendl_fd("42sh: echo: write error", 2);
	return (-1);
}

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
			return (echo_error());
		if (cmd[i + e + 1] && write(1, " ", 1) == -1)
			return (echo_error());
		i++;
	}
	if (e == 1)
		ft_putendl("\x1b[30;47m%\x1b[0m");
	else
		ft_putchar('\n');
	return (ret);
}
