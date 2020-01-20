/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 23:38:57 by mabayle           #+#    #+#             */
/*   Updated: 2019/12/17 00:21:51 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

t_21sh	*init_shell(void)
{
	t_21sh		*shell;

	shell = ft_memalloc(sizeof(*shell));
	shell->lex = NULL;
	shell->lex_size = 0;
	shell->ast = NULL;
	return (shell);
}

int     main(int argc, char **argv)
{
    if (argc == 2)
    {
        g_shell = init_shell();
		g_shell->line = argv[1];
        ft_putstr(PURPLE);
		ft_putendl("BTreeTest - Input :");
		ft_putstr(NC);
        ft_putendl(argv[1]);
		ft_lexer(&g_shell->lex, g_shell->line);
    } 
    else
        printf("Usage : ./BTreeTest + \"argument\"\n");
    return (0);
}