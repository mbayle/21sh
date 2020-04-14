/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ari.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 15:28:31 by geargenc          #+#    #+#             */
/*   Updated: 2020/04/14 08:00:05 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

int				ft_ari(char *expr, long *res, int rec)
{
	t_ari_lex	lex;
	t_ari_ast	ast;

	(void)rec;
	lex = (t_ari_lex){expr, 0, NULL, NULL};
	if (ft_ari_lexer(&lex))
		return (-1);
	ast = (t_ari_ast){expr, NULL, NULL, NULL};
	ft_ari_convert_lex(&lex, &ast);
	if (ft_ari_ast(&ast))
		return (-1);
	// ft_ari_ast_print(&ast);
	*res = 0;
	if (ast.begin)
	{
		if (g_ari_exetab[ast.begin->token](ast.begin, 0))
			return (-1);
		*res = ast.begin->value;
	}
	return (0);
}
