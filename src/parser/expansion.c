/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 03:47:18 by mabayle           #+#    #+#             */
/*   Updated: 2020/02/24 00:55:32 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"
#include <stdio.h>
#include <stdlib.h> // [DEBUG] just for test getenv

char	*value_env(char *input, int i)
{
 	char	*new;

  	new = ft_strdup("");
 	while (input[i] && !ft_isspace(input[i]) && input[i] != '$' &&
 			input[i] != ':' && input[i] != '"')
 		new = ft_strjoin_onef(new, input[i++]);
 	return (new);
}

char	*echo_verify_expand(char *input)
{
 	int		i;
 	char 	*var;
 	char	*new;

  	i = 0;
 	new = ft_strdup("");
 	while (input[i])
 	{
 		if (input[i] == '$' && ft_strlen(input) > 1)
 		{
 			var = value_env(input, i++ + 1);
 			new = ft_strjoin_free(new, ((getenv(var)) ? getenv(var) : "\0"));
 			free(var);
 			while (input[i] && !ft_isspace(input[i]))
 				i++;
 			input[i] ? new = ft_strjoin_onef(new, ' ') : 0;
 		}
 		else
 			new = ft_strjoin_onef(new, input[i]);
 		i++;
 	}
 	input[0] == '"' ? new = ft_strjoin_onef(new, '"') : 0;
 	ft_putstr(L_BLUE);
 	ft_putstr("    Echo special case ! Old / New value for token->next : ");
 	ft_putstr(NC);
 	ft_putendl(new);
 	return (new);
}

char	*dollar_expand(char *value)
{
 	char *new;

  	new = ft_strdup("");
 	if (value[0] == '$')
 		new = ft_strjoin_free(new, getenv(&value[1]));
 	ft_putstr(L_BLUE);
 	ft_putstr("    Dollar expansion work ! New value for lexeme : ");
 	ft_putstr(NC);
 	ft_putendl(new);
 	return (new);
}

char	*tilde_expand(char *value)
{
 	char *new;
	char *t;

	t = NULL;
  	new = ft_strdup("");
 	if (value[0] == '~')
 	{
 		if (value[1] == '+')
 			new = ft_strjoin_free(new, getenv("PWD"));
 		else if (value[1] == '-')
 			new = ft_strjoin_free(new, getenv("OLDPWD"));
        else if (value[1] == '/')
 		{
            new = ft_strjoin_free(new, getenv("HOME"));
            new = ft_strjoin_free(new, &value[1]);
        }
 		else
 			new = ft_strjoin_free(getenv("HOME"), new);
 	}
    if ((t = getenv("TERM")) == NULL)
		ft_putendl("[DEBUG] Getenv retourne NULL");
  	ft_putstr(L_BLUE);
 	ft_putstr("    Tilde expansion work ! New value for lexeme : ");
 	ft_putstr(NC);
 	ft_putendl(new);
 	return (new != NULL ? new : value);
}

void	verify_expansion(t_lex *lex)
{
 	ft_putstr(PURPLE);
 	ft_putendl("Expansion debug :");
 	ft_putstr(NC);
 	while (lex)
 	{
 		ft_putendl_col("Searching, please wait...", L_GRAY, NC);
 		if (lex->value[0] == '~' || lex->value[0] == '$' 
 			|| (ft_strcmp(lex->value, "echo") == 0))
 		{	
 			ft_putstr(GREEN);
 			ft_putstr("/!\\ Expand symbol find : ");
 			ft_putstr(NC);
 			ft_strcmp(lex->value, "echo") == 0 ? ft_putendl(lex->next->value)
 				: ft_putendl(lex->value);
 			if (lex->value[0] == '~')
 				lex->value = tilde_expand(lex->value);
 			else if (lex->value[0] == '$')
 				lex->value = dollar_expand(lex->value);
 			else if (ft_strcmp(lex->value, "echo") == 0)
 				lex->next->value = echo_verify_expand(lex->next->value);
 		}
 		else
 			ft_putendl_col("No expand symbol in this token", L_YELLOW, NC);
 		lex = lex->next;
 	}
 	write(1, "\n", 1);
}