/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 02:44:11 by mabayle           #+#    #+#             */
/*   Updated: 2020/03/12 05:19:36 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

void	ft_print_value(t_ast *ast, char *side, int lvl)
{
	t_lex *tmp;

	tmp = ast->lex;
	ft_putstr(RED);
	if (ft_strcmp(side, "root") == 0)
	{
		ft_putstr(ast->lex->value);
		ft_padding(lvl);
		return ;
	}
	if (!ast->left && !ast->right)
	{
		while (tmp)
		{
			if (tmp->token == UNKNOWN)
				break ;
			ft_putstr(tmp->value);
			ft_putstr(" ");
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp)
		{
			ft_putstr(tmp->value);
			tmp = tmp->next;
		}
	}
}

void	ft_print_node(t_ast *ast, char *side, int lvl)
{
	ft_padding(lvl);
	ft_putstr("** ");
	ft_strcmp(side, "right") == 0 ? ft_putstr(YELLOW) : ft_putstr(GREEN);
	ft_putstr(side);
	ft_putnbr(lvl);
	ft_putstr(WHITE);
	ft_putendl(" **");
	ft_padding(lvl);
	ft_print_value(ast, side, lvl);
	ft_putendl(WHITE);
	ft_padding(lvl);
	ft_putendl("***********");
	(void)ast;
}

void	ft_print_ast(t_ast *ast, char *side, int lvl)
{
	if (!ast)
		return ;
	if (ast->right)
		ft_print_ast(ast->right, "right", ++lvl);
	else
		++lvl;
	ft_print_node(ast, side, lvl);
	if (ast->left)
		ft_print_ast(ast->left, "left", lvl--);
	else
		--lvl;
}

void	ft_putast(t_ast *ast)
{
	if (ast)
	{
		ft_putendl_col("AST debug :\n", PURPLE, WHITE);
		ft_print_ast(ast, "root", 0);
	}
}
