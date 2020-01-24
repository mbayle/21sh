/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 09:58:33 by mabayle           #+#    #+#             */
/*   Updated: 2018/04/18 21:16:22 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	new_n;

	new_n = n;
	if (n < 0)
	{
		new_n = new_n * (-1);
		ft_putchar_fd('-', fd);
	}
	if (new_n > 9)
		ft_putnbr_fd(new_n / 10, fd);
	ft_putchar_fd(new_n % 10 + '0', fd);
}
