/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2putstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 22:46:34 by frameton          #+#    #+#             */
/*   Updated: 2019/09/14 23:42:30 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_2putstr_fd(char const *s, char const *s2, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
	if (s2)
		write(fd, s2, ft_strlen(s2));
}
