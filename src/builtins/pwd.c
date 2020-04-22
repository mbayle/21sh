/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 14:45:11 by ymarcill          #+#    #+#             */
/*   Updated: 2020/04/22 14:45:12 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int	mypwd(void)
{
	char	*pwd;

	if (!(pwd = get_myenv("PWD")))
		pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	ft_putendl(pwd);
	ft_strdel(&pwd);
	return (0);
}
