/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 02:08:05 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/19 22:12:00 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		list_size(t_lex *lex)
{
	int i;

	i = 0;
	while (lex && lex->next)
	{
		i += ft_strlen(lex->value);
		lex = lex->next;
	}
	return (i);
}

int		lex_size(t_lex *lex)
{
	int i;

	i = 0;
	while (lex)
	{
		i++;
		lex = lex->next;
	}
	return (i);
}

char	*list_to_string(t_lex *lex)
{
//	int		i;
	char	*dst;

//	i = 0;
	if (lex == NULL || (dst = ft_strnew(1)) == NULL)
		return (NULL);
	while (lex && lex->token != UNKNOWN)
	{
		if (lex->token == ASSIGN_WORD)
			dst = ft_strjoinfree(dst, "\r");
		dst = ft_strjoinfree(dst, lex->value);
		if (lex->next && lex->token != IO_NUMBER)
			dst = ft_strjoinfree(dst, " ");
		lex = lex->next;
	}
	return (dst);
}

char	**list_to_tab(t_lex *lex)
{
	int		i;
	char	**dst;

	i = 0;
	if (!(dst = malloc(sizeof(char*) * (lex_size(lex) + 1))))
		malloc_exit();
	while (lex && lex->token != UNKNOWN)
	{
		if (lex->token == ASSIGN_WORD)
		{
			dst[i] = ft_strdup("\r");
			dst[i] = ft_strjoinfree(dst[i], lex->value);
		}
		else if (lex->token == IO_NUMBER)
		{
			dst[i] = ft_strjoin(lex->value, lex->next->value);
			lex = lex->next;
		}
		else
			dst[i] = ft_strdup(lex->value);
		lex = lex->next;
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

void	join_job_line(t_ast *ast, int p_pos)
{
	char	*tmp;
	char	*tmp2;

	g_jobcontrol.arg[g_jobcontrol.index] = list_to_tab(ast->lex);
	g_jobcontrol.index++;
	tmp = ft_strdup(g_jobcontrol.first_job->command);
	tmp2 = list_to_string(ast->lex);
	ft_strdel(&g_jobcontrol.first_job->command);
	if (tmp)
		g_jobcontrol.first_job->command = ft_strjoin(tmp, tmp2);
	else
		g_jobcontrol.first_job->command = ft_strdup(tmp2);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	if (p_pos != 1)
	{
		g_jobcontrol.first_job->command =
		ft_strjoinfree(g_jobcontrol.first_job->command, " | ");
		if (!(g_jobcontrol.arg[g_jobcontrol.index] = malloc(sizeof(char*) * 2)))
			return (malloc_exit());
		g_jobcontrol.arg[g_jobcontrol.index][0] = ft_strdup("|");
		g_jobcontrol.arg[g_jobcontrol.index][1] = NULL;
		g_jobcontrol.index++;
	}
	g_jobcontrol.arg[g_jobcontrol.index] = NULL;
}
