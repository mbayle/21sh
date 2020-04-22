/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expanse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 18:26:39 by geargenc          #+#    #+#             */
/*   Updated: 2020/04/22 15:18:13 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_global.h"
#include "../../includes/projectinclude.h"

char			*ft_expanse_word(char *word)
{
	t_txtlist	*list;
	char		*result;

	list = ft_parse_word(word);
	g_jobcontrol.stopexe = 0;
	if (ft_exp(list))
	{
		g_jobcontrol.stopexe = 1;
		return (NULL);
	}
	result = ft_txt_join(list);
	return (result);
}

char			**ft_command_to_args(char **args)
{
	if (!ft_expanse_args(args))
		return (NULL);
	args = ft_field_split(args);
	ft_rmquotes_args(args);
	return (args);
}

char			*ft_simple_expanse(char *word)
{
	char		*new;

	if ((new = ft_expanse_word(word)))
		ft_rmquotes_word(new);
	return (new);
}
