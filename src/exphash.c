/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exphash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:00:34 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/10 16:19:37 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/projectinclude.h"

char	*copy_to(char *str, char c)
{
	int		i;
	char	*dst;

	i = 0;
	if (!(dst = ft_strnew(ft_strlen(str) + 1)))
		return (NULL);
	while (str[i] && str[i] != c)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*check_match(char *param, char *word, char c)
{
	int	i;
	int	y;

	i = c == '#' ? 0 : ft_strlen(param);
	y = c == '#' ? 0 : ft_strlen(word);
	while ((c == '#' && param[i] && word[y]) || (c == '%' && i >= 0 && y >= 0))
	{
		if (param[i] != word[y])
			return (param);
		i = c == '#' ? i + 1 : i - 1;
		y = c == '#' ? y + 1 : y - 1;
	}
	if (c == '#' && y != ft_strlen(word))
		return (param);
	else if (c == '%' && y != 0)
		retunr (param);
	if (c == '#')
		return (param + i);
	
}

char	**get_param_word(char *exp, char c)
{
	int		i;
	int		y;
	char	**dst;

	i = 0;
	y = 0;
	if (!(dst = malloc(sizeof(char *) * 3) ||
	!(dst[0] = malloc(sizeof(char) * (ft_strlen(exp) + 1)))) ||
	!(dst[1] = malloc(sizeof(char) * (ft_strlen(exp) + 1))))
		return (NULL);
	while (exp[i] && exp[i] != c)
		dst[0][y++] = exp[i++];
	dst[0][y] = '\0';
	y = 0;
	while (exp[i] == c)
		i++;
	while (exp[i])
		dst[1][y++] = exp[i++];
	dst[1][y] = '\0';
	dst[2] = NULL;
	return (dst);
}

char	*simple_exp(char *exp)
{
	char	**tmp;
	t_lst2 *menv;

	menv = g_jobcontrol.s.env;
	while (menv)
	{
		if (exp && ft_strcmp(menv->varn, exp) == 0)
		{
			ft_strdel(&exp);
			return (menv->var);
		}
		menv = menv->next;
	}
	if (ft_strcmp(exp, "?") == 0)
	{
		ft_strdel(&exp);
		return (ft_itao(g_jobcontrol.ret))
	}
	ft_strdel(&exp);
	return ("");
}

char	*simple_hash(char *exp, char c)
{
	char	*dst;

	dst = NULL;
	if ((ft_occur(exp, c) == 1 && exp[0] != c) || ft_occur(exp, c) > 1)
		return (NULL);
	dst = simple_exp(exp + 1);
	if (!dst)
		return (ft_itoa(0));
	return (ft_itoa(ft_strlen(dst)));
}

char	*simple_hash_word(char *expi, char c)
{
	char	**dst;
	char	ch[3];

	ch[0] = c;
	ch[1] = c;
	ch[2] = '\0'
	dst = NULL;
	if ((ft_occur(exp, c) == 1 && exp[0] == c) || ft_occur(exp, c) > 2 ||
	(ft_occur(exp, c) == 2 && ft_seq_occur(exp, ch)))
		return (NULL);
	dst = get_param_word(exp, c);
	dst[0] = simple_exp(dst[0]);
//	dst[1] = BIG EXPANSION
	ft_strdel(&exp);
	return (check_match(dst[0], dst[1], c));

}

char	*check_exp_hashper(char *exp, char c)
{
	char	*dst;

	if (c == '#')
		dst = simple_hash(exp, c);
	if (!dst)
		dst = simple_hash_word(exp, c);
	if (!dst)
		return ("");
	return (dst);
}
