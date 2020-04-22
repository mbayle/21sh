/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_gestion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 04:48:49 by mabayle           #+#    #+#             */
/*   Updated: 2020/04/20 16:48:20 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

void	tokerr(int i)
{
	if (i == 1)
		putendcol("Shell : Missing brace", RED, WHITE);
	else
		putendcol("Shell : Missing quote", RED, WHITE);
}

int		io_case(int i, int *io_nbr, char *input)
{
	if (!ft_strncmp(input + i, ">", 1) || !ft_strncmp(input + i, "<", 1))
		*io_nbr = 1;
	i = find_end(i, input);
	return (i);
}
