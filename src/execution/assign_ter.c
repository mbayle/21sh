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
	char	**tmp2;

	i = 0;
	while (ass && ass[i] && ass[i][0] == '\r')
	{
		tmp = ft_strdup(ass[i]);
		free(ass[i]);
		ass[i] = ft_strdup(tmp + 1);
		i++;
	}
	tmp2 = get_key(ass);
	dst = get_key(ass);
	g_jobcontrol.ret = unsetloc(dst);
//	g_jobcontrol.ret = myunsetenv(tmp2);
	ft_freetab(dst);
	ft_freetab(tmp2);
//	t_myloc *loc;

//	loc = g_jobcontrol.myloc;
//	while (loc)
//	{
//		//ft_putendl(loc->keyval);
//		loc = loc->next;
//	}
}
