/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 04:53:07 by mabayle           #+#    #+#             */
/*   Updated: 2019/11/07 03:07:49 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/parser.h"

/*
** TEMPORARY MAIN - JUST FOR TEST TOKENIZER PARSER AND AST
*/

t_21sh	*init_shell(void)
{
	t_21sh		*shell;

	shell = ft_memalloc(sizeof(*shell));
	shell->lex = NULL;
	shell->lex_size = 0;
	shell->ast = NULL;
	return (shell);
}

/*
** TO DO LIST :
**		- Refaire le main et penser a remettre shell->lex_size a 0 avant une nouvelle boucle)
*/

#include <stdio.h>
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
		printf("[DEBUG][MAIN.C][MAIN] Nombre de token = %d", g_shell->lex_size);
		ft_parse(&g_shell->lex, &g_shell->ast);
	}
	return (0);
}
