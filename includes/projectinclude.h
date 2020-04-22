/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectinclude.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 04:05:42 by mabayle           #+#    #+#             */
/*   Updated: 2020/04/22 16:17:24 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECTINCLUDE_H
# define PROJECTINCLUDE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "jobcontrol.h"
# include "input.h"
# include "get_next_line.h"
# include "linedition.h"
# include "../libft/includes/libft.h"
# include "lexer.h"
# include "grammar.h"
# include "parser.h"
# include "mybtree.h"
# include "exp.h"

t_21sh		*init_shell(int debug);
static void	init_term(t_struct *s);
void		init_struct(t_struct *s, char **envp);
void		init_myenv(char **envp);
void		init_myloc(char **envp);
void		init_jc(char **env);

#endif
