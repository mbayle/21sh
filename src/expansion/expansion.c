/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 21:14:06 by mabayle           #+#    #+#             */
/*   Updated: 2020/03/09 01:30:38 by mabayle          ###   ########.fr       */
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

/*char    *ft_expansion(char *str)
{
    if (not_expand(str) == 0)
        return (str);
    if (ft_strncmp(str, "${", 2) == 0)
    {
        if (str[ft_strlen(str)] != '}')
            return (NULL);
        // A FAIRE APRES POUR GERER LES BRACES EXPANSIONS
    }
    if (str[0] == '~')
        return (tilde_expand(str));
    if (str[0] == '$')
        return (simple_expand(str));
}*/