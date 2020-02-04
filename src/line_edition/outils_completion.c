/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_completion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 22:07:12 by frameton          #+#    #+#             */
/*   Updated: 2020/02/03 22:07:13 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_htr		*create_lst_comp2(char ***del, char ***path)
{
	free_dchar(&*del);
	*path = NULL;
	return (NULL);
}

int			sec_free(char **s, int i)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	return (i);
}

static int	putchar_completion_b(char **line, int c, t_struct *s)
{
	char	*del;

	del = *line;
	while (c--)
		del++;
	if (s->cpt == 2 || s->cpt == 3)
	{
		if ((s->comp.name = ft_mstrcpy(NULL, del)) == NULL)
			return (0);
		s->comp.sz = ft_strlen(del);
	}
	else
	{
		while (*del)
			if (!(putchar_completion2(s, *del++)))
				return (0);
	}
	return (1);
}

int			putchar_completion(t_struct *s, t_htr **bcom, char **line, int c)
{
	t_htr	*com;
	t_htr	*save;
	char	*l;

	com = *bcom;
	save = *bcom;
	l = NULL;
	if (c < 2 || !com)
		return (sec_free(line, 0));
	create_line_comp(line, com, *bcom, c);
	*bcom = save;
	if (c == (int)ft_strlen(*line))
		return (sec_free(line, 1));
	if (!(putchar_completion_b(line, c, s)))
		return (sec_free(line, -1));
	return (sec_free(line, 2));
}
