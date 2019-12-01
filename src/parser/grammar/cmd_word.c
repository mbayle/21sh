/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 01:57:47 by mabayle           #+#    #+#             */
/*   Updated: 2019/12/01 05:47:06 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"

/*
** Objectif de a fonction : check if str is a valid name (posix grammar)
**                          Definition :
**                          In the shell command language, a word consisting 
**                          solely of underscores, digits, and alphabetics
**                          from the portable character set. 
**                          The first character of a name is not a digit.
** Valeur de retour : return 1 if str is a valid name | else return 0
*/
int     valid_name(char *str)
{
      int i;

      i = 0;
      if (ft_isdigit(str[i]) == 1)
        return (0);
      while (str[i] != '\0')
      {
          if ((ft_isdigit(str[i]) == 1) || (str[i] >= 'A' && str[i] <= 'Z')
                || (str[i] >= 'a' && str[i] <= 'z') || str[i] == '_')
                i++;
          else
                return (0);
      }
      return (1);
}

/*
** Objectif de la fonction : check if lex->next->value == WORD and apply
                             rule 7b of posix grammar : 
                             If the TOKEN contains an unquoted (as determined 
                             while applying rule 4 from Token Recognition) 
                             <equals-sign> character that is not part of an 
                             embedded parameter expansion, command 
                             substitution, or arithmetic expansion construct 
                             (as determined while applying rule 5 from Token
                             Recognition):
                                - If the TOKEN begins with '=', then rule 1 
                                  shall be applied.
                                - If all the characters in the TOKEN 
                                  preceding the first such <equals-sign> 
                                  form a valid name (see XBD Name), 
                                  the token ASSIGNMENT_WORD shall be returned.
                                - Otherwise, it is unspecified whether rule 1
                                  is applied or ASSIGNMENT_WORD is returned.
                            Otherwise, rule 1 shall be applied.
                            Assignment to the name within a returned 
                            ASSIGNMENT_WORD token shall occur as specified in
                            Simple Commands.
** Valeur de retour : return 1 if match | else return 0
*/
int     cmd_word(t_lex *lex)
{
    char  *check;
    int   i;

    check = NULL;
    i = 0;
    if (lex->token != WORD)
        return (0);
    else if (lex->value[0] == '=')
        return (1);
    else if (ft_strchr(lex->value, '=') != NULL)
    {
        while (lex->value[i] != '=')
        {
            check[i] = lex->value[i];
            i++;
        }
        if (valid_name(check) == 1)
            lex->token = ASSIGN_WORD;
        return (1);
    }
    else
        return (0);    
}