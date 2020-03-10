/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 00:53:04 by frameton          #+#    #+#             */
/*   Updated: 2020/03/10 00:53:18 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int		digit_or_str(char *str)
{
	int i;

	i = 0;
	if (str)
	{
		if (ft_isdigit(str[i]) == 1)
			return (0);
		if (str[i] == '+' || str[i] == '-')
		{
			i++;
			if (ft_isdigit(str[i]) == 1)
				return (0);
		}
	}
	return (1);
}

int		fc_get_index(char *str)
{
	t_list		*history;
	char		*buf;
	int			i;

	if (!g_tracking.mysh->hist)
		return (fc_error(4, str));
	if (!str || eq_sign(str) > 0)
		return (-42);
	history = ft_lstgetlast(g_tracking.mysh->hist->firstelement);
	if (!history)
		return (fc_error(4, str));
	i = ft_strlen(str);
	while (history)
	{
		buf = history->content;
		if (ft_strncmp(str, buf, i) == 0)
			return (history->index);
		history = history->prev;
	}
	return (fc_error(4, str));
}

void	char_to_index(t_fc *f)
{
	int		tmp;

	tmp = 0;
	if (digit_or_str(f->frst) == 0)
		f->min = ft_atoi(f->frst);
	else
	{
		if (eq_sign(f->frst) == 1)
		{
			if (f->s != 1)
				parse_error(5, NULL);
			else
				f->min = -4;
		}
		else
			f->min = fc_get_index(f->frst);
	}
	if (digit_or_str(f->scd) == 0)
		f->max = ft_atoi(f->scd);
	else
		f->max = fc_get_index(f->scd);
	if (f->min > f->max && f->s != 1)
		rev_list(f);
}
