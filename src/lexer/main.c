/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 04:53:07 by mabayle           #+#    #+#             */
/*   Updated: 2019/09/03 05:20:51 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

/*
** TEMPORARY MAIN - JUST FOR TEST TOKENIZER
*/

t_21sh	*init_shell(void)
{
	t_21sh		*shell;

	shell = ft_memalloc(sizeof(*shell));
	shell->lex = NULL;
	shell->ast = NULL;
	return (shell);
}

int		main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage:\n  - 1 arg possible (ex : ./test 'Hello world !')");
	}
	else
	{
		g_shell = init_shell();
		g_shell->line = argv[1];
		ft_lexer(&g_shell->lex, g_shell->line);
	}
	return (0);
}
