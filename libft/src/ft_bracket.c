/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bracket.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 04:48:49 by mabayle           #+#    #+#             */
/*   Updated: 2020/03/11 19:51:17 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int  match(char top, char a)
{
    if (top)
    {
        if (top == '(' && a == ')')
            return (1);
        if (top == '{' && a == '}')
            return (1);
        if (top == '[' && a == ']')
            return (1);
    }
    return (0);
}
int         ft_bracket(char *str, int top, int a, char *stack)
{
    while (str[a])
    {
        if (str[a] == '(' || str[a] == '{' || str[a] == '[')
        {
            top++;
            stack[top] = str[a];
        }
        if (str[a] == ')' || str[a] == '}' || str[a] == ']')
        {
            if (stack[top] == 0)
            {
                write(1, "Case 1\n", 7);
                if (str[a] == '}')
                    return (-1);
                if (str[a] == ')')
                    return (-2);
                return (0);
            }
            else if (!(match(stack[top], str[a])))
            {
                write(1, "Case 2\n", 7);
                if (str[a] == '}')
                    return (-1);
                if (str[a] == ')')
                    return (-2);
                return (0);
            }
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
