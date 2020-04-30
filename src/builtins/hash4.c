/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 14:58:57 by ymarcill          #+#    #+#             */
/*   Updated: 2020/04/29 19:52:00 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"
#include <sys/mman.h>
#define PATHVAR "PATH="

void				rec_print_hash(t_hash *hash)
{
	int				i;

	if (hash->path)
	{
		if (number_size(hash->hits) <= 4)
			write(1, "    ", (4 - number_size(hash->hits)));
		ft_putnbr(hash->hits);
		ft_putstr("    ");
		ft_putendl(hash->path);
	}
	i = 0;
	while (i < 256)
	{
		if (hash->next[i])
			rec_print_hash(hash->next[i]);
		i++;
	}
}

void				print_hash(t_hash *hash)
{
	if (hash)
	{
		ft_putendl("hits    command");
		rec_print_hash(hash);
	}
}

int					hash_invalid_opt(char opt)
{
	ft_putstr_fd("42sh: hash: -", 2);
	ft_putchar_fd(opt, 2);
	ft_putendl_fd(": invalid option", 2);
	return (2);
}

int					hash_not_found(char *cmd)
{
	ft_putstr_fd("42sh: hash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": not found", 2);
	return (1);
}

int					hash_add(t_hash **hash, char *pathvar, char **cmd)
{
	int				ret_value;
	t_hash			*ret;

	ret_value = 0;
	while (*cmd)
	{
		ret = add_command(*cmd, pathvar, hash);
		if (ret == MAP_FAILED)
			exit(2);
		if (ret == NULL)
			ret_value = hash_not_found(*cmd);
		cmd++;
	}
	return (ret_value);
}
