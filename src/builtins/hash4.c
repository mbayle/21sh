/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 14:58:57 by ymarcill          #+#    #+#             */
/*   Updated: 2020/04/22 14:59:25 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"
#include <sys/mman.h>
#define PATHVAR "PATH="

void				rec_print_hash(t_hash *hash)
{
	int				i;

	if (hash->path)
		printf("%4d    %s\n", hash->hits, hash->path);
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
		printf("hits    command\n");
		rec_print_hash(hash);
	}
}

int					hash_invalid_opt(char opt)
{
	printf("shell: hash: -%c: invalid option\n", opt);
	return (2);
}

int					hash_not_found(char *cmd)
{
	printf("shell: hash: %s: not found\n", cmd);
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
