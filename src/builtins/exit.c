/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:01:27 by mabayle           #+#    #+#             */
/*   Updated: 2020/02/17 22:19:21 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>
#include "linedition.h"

int		ft_exit(t_shell *shellcore, int nbr)
{
	free_after_exit(shellcore->env_lst, shellcore->hist_lst, shellcore->path);
	ft_strdel(&shellcore->history_path);
	ft_strdel(&shellcore->home_env_var);
	free(shellcore);
	exit_edl(g_lined);
	exit(nbr);
}

int		ft_atoi_exit(char *str)
{
	size_t	output;
	int		i;
	int		mult;

	output = 0;
	i = 0;
	mult = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		mult = (str[i] == '-') ? -1 : 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		output = output * 10 + str[i++] - 48;
	if (output > INT_MAX || (int)output < INT_MIN)
		return (display_error("21sh: exit: integer is expected\n", NULL));
	free(str);
	return (output * mult);
}

int		parse_exit(t_shell *shellcore, char **command)
{
	int		e;

	e = 0;
	if (command[2])
	{
		ft_putstr_fd("21sh: exit: Too many arguments\n", 2);
		return (ft_exit(shellcore, 255));
	}
	else
		return (ft_exit(shellcore, ft_atoi_exit(command[1])));
}

int		find_exit(t_shell *shellcore, char **command)
{
	ft_putstr_fd("exit\n", 2);
	if (command[1])
		return (parse_exit(shellcore, command));
	return (ft_exit(shellcore, 0));
}
