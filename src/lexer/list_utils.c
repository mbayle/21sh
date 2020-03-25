/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 05:17:16 by mabayle           #+#    #+#             */
/*   Updated: 2020/03/25 00:51:56 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"
#include "libft.h"

/*
** Purpose of the function : Create new node
**							Initialize all variables and set name and position
** Return value : New node
*/

t_lex	*list_new(char *input)
{
	t_lex	*new;

	if (!(new = ft_memalloc(sizeof(*new))))
		return (NULL);
	if (input == NULL)
		new->value = NULL;
	else
		new->value = ft_strdup(input);
	new->hdoc = NULL;
	new->pos = g_shell->lex_size;
	new->token = 0;
	new->operator = 0;
	new->hdoc_delim = 0;
	new->priority = 0;
	new->escape = 0;
	new->next = NULL;
	return (new);
}

/*
** Purpose of the function : Add to the end of list
** Return value : no return
*/

void	list_add(t_lex **alst, t_lex *new)
{
	t_lex		*tmp;

	if (alst == NULL)
		return ;
	tmp = *alst;
	if (*alst == NULL)
		*alst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

/*
** Purpose of the function : Find next element of my list
** Return value : Return the last element
*/

t_lex	*lex_last(t_lex *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*
** Purpose of the function : Free variables in node
** Return value : no return
*/

#include <stdio.h>
void	lex_suppr_elem(t_lex **elem)
{
	t_lex	*suppr;

	suppr = *elem;
	*elem = (*elem)->next;
	ft_2eputendl("DEBUG SUPPR VALUE FREE -> ", suppr->value);
	(*elem) ? ft_2eputendl("DEBUG ELEM VALUE FREE -> ", (*elem)->value) : 0;
	if (suppr->value)
		ft_strdel(&suppr->value);
	if (suppr->hdoc)
		ft_strdel(&suppr->hdoc);
	//suppr->next = NULL;
	if (suppr)
	{
		free(suppr);
		suppr = NULL;
	}
}

/*
** Purpose of the function : loop on my entire list and call anathor function
**							for free each node
** Return value : no return
*/

void	lexdel(t_lex **alst)
{
	t_lex	*current;

	if (!alst)
		return ;
	current = *alst;
	while (current)
		lex_suppr_elem(&(current));
	*alst = NULL;
	g_shell->lex_size = 0;
}
