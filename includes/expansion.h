/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 21:07:51 by mabayle           #+#    #+#             */
/*   Updated: 2020/03/10 03:57:12 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "projectinclude.h"

/*
********************************************************************************
*/

/*
** expansion.c
*/
int					 not_expand(char *str);
char				*search_varloc(char *search);

/*
** param_expand.c
*/
char				*parameter_get_word(char *input);
char				*parameter_minus(char *input);
char				*parameter_expansion(char *input);

#endif
