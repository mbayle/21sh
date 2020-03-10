/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exphash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:00:34 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/10 14:35:43 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/projectinclude"

char	**get_param_word(char *exp)
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
	while (exp[i] && exp[i] != '#')
		dst[0][y++] = exp[i++];
	dst[0][y] = '\0';
	y = 0;
	while (exp[i] == '#')
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
			return (menv->var);
		menv = menv->next;
	}
	if (ft_strcmp(exp, "?") == 0)
		return (ft_itao(g_jobcontrol.ret))
	return (NULL);
}

char	*simple_hash(char *exp)
{
	char	*dst;

	dst = NULL;
	if ((ft_occur(exp, '#') == 1 && exp[0] != '#') || ft_occur(exp, '#') > 1)
		return (NULL);
	dst = simple_exp(exp + 1);
	if (!dst)
		return (ft_itoa(0));
	return (ft_itoa(ft_strlen(dst)));
}

char	*simple_hash_word(char *exp)
{
	char	**dst;

	dst = NULL;
	if ((ft_occur(exp, '#') == 1 && exp[0] == '#') || ft_occur(exp, '#') > 1)
		return (NULL);
	dst = get_param_word(exp);

}

char	*check_exphash(char *exp)
{
	char	*dst;

	dst = simple_hash(exp);
	if (!dst)
		dst = 
}
