/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bracket.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 04:48:49 by mabayle           #+#    #+#             */
/*   Updated: 2020/03/11 06:01:45 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	match(char top, char a)
{
	if (top)
	{
		if (top == '(' && a == ')')
			return (1);
		if (top == '{' && a == '}')
			return (1);
	}
	return (0);
}

int			ft_bracket(char *str, int top, int a, char *stack)
{
	while (str[a])
	{
		if (str[a] == '(' || str[a] == '{')
		{
			top++;
			stack[top] = str[a];
		}
		if (str[a] == ')' || str[a] == '}')
		{
			if (top == -1 || stack[top] == 0)
				return (str[a] == '}' ? -1 : -2);
			else if (top == -1 || (stack[top] && !(match(stack[top], str[a]))))
				return (str[a] == '}' ? -1 : -2);
			else
			{
				stack[top] = 0;
				top--;
			}
		}
		a++;
	}
	if (top == -1)
		return (a);
	return (0);
}
