/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 22:55:09 by frameton          #+#    #+#             */
/*   Updated: 2020/03/10 18:48:45 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

char	*mini_strjoin(char *s1, char *s2)
{
	char	*dest;
	char	*sa;

	sa = NULL;
	while (*s1 && *s1 != '=')
		s1++;
	s1++;
	if (s1 && s2)
	{
		if ((dest = ft_strnew((ft_strlen((char *)s1) + ft_strlen((char *)s2))))
				== NULL)
			return (NULL);
		sa = dest;
		dest = ft_strcpy(dest, s1);
		dest = ft_pstrback(dest);
		dest++;
		dest = ft_strcpy(dest, s2);
	}
	return (sa);
}

int		create_path_home(t_struct *s, char *new, int i)
{
	t_lst2		*l;
	char		*tmp;

	l = (*s).env;
	while (l && (ft_strncmp(l->env, "HOME", 4) != 0))
		l = l->next;
	if (!l)
	{
		ft_eputstr(MAGENTA"warning"WHITE": the home variable doesn't exist.\n");
		return (0);
	}
	else
	{
		tmp = (*s).av[i];
		tmp++;
		if ((new = mini_strjoin(l->env, tmp)) == NULL)
			return (-1);
		tmp--;
		free_char(&tmp);
		(*s).av[i] = new;
	}
	return (1);
}
