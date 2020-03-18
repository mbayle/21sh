/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_ter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 22:57:02 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/12 22:58:16 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

void	unexec_ass(char **ass)
{
	int		i;
	char	*tmp;
	char	**dst;

	i = 0;
	while (ass && ass[i] && ass[i][0] == '\r')
	{
		tmp = ft_strdup(ass[i]);
		free(ass[i]);
		ass[i] = ft_strdup(tmp + 1);
		i++;
	}
	dst = get_key(ass);
//	ft_printtab(dst);
	g_jobcontrol.ret = exec_unset(&g_jobcontrol.s, dst);
	ft_freetab(dst);
}
