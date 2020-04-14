/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expanse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 18:26:39 by geargenc          #+#    #+#             */
/*   Updated: 2020/03/21 07:38:11 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/ft_global.h"
#include "../../includes/projectinclude.h"

// char			**ft_init_args(t_node *current)
// {
// 	char		**args;
// 	t_node		*tmp;
// 	int			i;

// 	i = 0;
// 	tmp = current;
// 	while ((tmp = tmp->right))
// 		i++;
// 	args = (char **)malloc_exit((i + 1) * sizeof(char *));
// 	i = 0;
// 	tmp = current;
// 	while ((tmp = tmp->right))
// 	{
// 		if (!(args[i] = ft_strdup(tmp->data)))
// 			exit(2);
// 		i++;
// 	}
// 	args[i] = NULL;
// 	return (args);
// }

char			*ft_expanse_word(char *word)
{
	t_txtlist	*list;
	char		*result;

	list = ft_parse_word(word);
	g_jobcontrol.stopexe = 0;
	if (ft_exp(list))
	{
		g_jobcontrol.stopexe = 1; // En cas d'erreur d'expension liee a une faute de syntaxe ou un test ${param:?word} stopexe mis a true
		return (NULL);
	}
	result = ft_txt_join(list);
//	printf("%p\n", list->data);
	if (list && list->data)
		ft_memdel((void**)&list->data);
	ft_memdel((void**)&list);
	return (result);
}

// char			**ft_command_to_args(t_node *current, t_42sh *shell)
// {
// 	char		**args;

// 	args = ft_init_args(current);
// 	if (!ft_expanse_args(args, shell))
// 		return (NULL);
// 	args = ft_field_split(args, shell);
// 	ft_rmquotes_args(args);
// 	return (args);
// }

char			**ft_command_to_args(char **args)
{
//	ft_printtab(args);
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
	ft_strdel(&word);
	return (new);
}
