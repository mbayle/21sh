/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_e2putstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 23:51:37 by frameton          #+#    #+#             */
/*   Updated: 2019/08/03 23:51:38 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_e2putstr(char const *s, char const *s2)
{
	if (s)
		write(2, s, ft_strlen(s));
	if (s2)
		write(2, s2, ft_strlen(s2));
}