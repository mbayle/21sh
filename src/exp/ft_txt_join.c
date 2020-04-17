/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_txt_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:33:14 by geargenc          #+#    #+#             */
/*   Updated: 2020/03/21 06:55:47 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

size_t			ft_txt_len(t_txtlist *list)
{
	size_t		count;

	count = 0;
	while (list)
	{
		list->len = ft_strlen(list->data);
		count = count + list->len;
		list = list->next;
	}
	return (count);
}

char			*ft_txt_join(t_txtlist *list)
{
	t_txtlist	*tmp;
	char		*word;
	size_t		size;

	word = (char *)ft_malloc_exit((ft_txt_len(list) + 1) * sizeof(char));
	word[0] = '\0';
	size = 0;
	while (list)
	{
		ft_strcpy(word + size, list->data);
		size = size + list->len;
		tmp = list;
//		printf("%s %p\n", "tmp = list", tmp);
		list = list->next;
		ft_memdel((void**)&tmp->data);
		//printf("%p\n", tmp->data);
		ft_memdel((void**)&tmp);
//		printf("%s %p\n", "free tmp", tmp);
	}
	return (word);
}
