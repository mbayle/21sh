/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 21:14:06 by mabayle           #+#    #+#             */
/*   Updated: 2020/03/09 19:51:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

/*
** General information : Order of expansions is: 
**                      1 - brace expansion
**                      2 - tilde expansion
**                      3 - parameter and variable expansion
**                      4 - quote removal (another file)
*/

int     not_expand(char *str)
{
    if (!str || str[0] != '$' || str[0] != '"' || str[0] != '~')
        return (0);
    else
        return (1);
}

char    *search_varloc(char *search)
{
    t_lst2 *tmp;

    tmp = g_lined->env;
    while (tmp)
    {
        if (tmp->lcl == 1 && (ft_strcmp(tmp->varn, search) == 0))
            return (tmp->var);
        tmp = tmp->next;
    }
    return (NULL);
}