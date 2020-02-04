/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rfrontws.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 18:11:11 by frameton          #+#    #+#             */
/*   Updated: 2018/04/25 18:02:43 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_pfrontws(char *str)
{
	if (str)
	{
		while ((*str >= 9 && *str <= 13) || *str == 32)
			str++;
	}
	return (str);
}