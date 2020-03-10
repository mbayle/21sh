/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_alias.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 23:48:26 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/10 01:09:15 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


char	

char	*

char	*check_alias(char *word)
{
	char	*dst;
	t_alias	*al;

	al = g_jobconctrol.alias;
	while (al)
	{
		if (al->key && word && ft_strcmp(al->key, word) == 0)
		{
			
		}
	}
}
