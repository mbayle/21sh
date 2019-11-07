/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserV2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 04:00:43 by mabayle           #+#    #+#             */
/*   Updated: 2019/11/07 05:24:19 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** TO DO LIST : - Faire toutes les fonctions selon la gram posix
*/

#include "../../includes/parser.h"

/*
// Program
ASTreeNode *program();		// test all posibilities
ASTreeNode *program1(); 	// linebreak, complete_commands, linebreak
ASTreeNode *program2();		// linebreak

// Complete_commands
ASTreeNode *complete_cmds();	// test all posibilities
ASTreeNode *complete_cmds1();	// complete_commands, newline_list, complete_commands
ASTreeNode *complete_cmds2();	// complete_commands

// Complete_command
ASTreeNode *complete_cmd();	// test all posibilities
ASTreeNode *complete_cmd1();	// list, separator_op
ASTreeNode *complete_cmd2();	// list

// List
ASTreeNode *list();		// test all posibilities
ASTreeNode *list1();		// list, separator_op, and_or
ASTreeNode *list2();		// and_or

// And_Or
ASTreeNode *and_or();		// test all posibilities
ASTreeNode *and_or1();		// and_or, AND_IF, linebreak, pipeline
ASTreeNode *and_or2();		// and_or, OR_IF, linebreak, pipeline
ASTreeNode *and_or3();		// pipeline

// Pipeline
ASTreeNode *pipeline();		// test all posibilities
ASTreeNode *pipeline1();	// bang, pipeline
ASTreeNode *pipeline2();	// pipeline

// Pipe_sequence
ASTreeNode *pipe_sequence();	// test all posibilities
ASTreeNode *pipe_sequence1();	// pipe_sequence, '|', linebreak, command
ASTreeNode *pipe_sequence2();	// command

// Command
ASTreeNode *command();		// simple_command

// Name
ASTreeNode *name();		// NAME [APPLY RULE 5]

// Wordlist
ASTreeNode *wordlist();		// test all posibilities
ASTreeNode *wordlist1();	// wordlist, WORD
ASTreeNode *wordlist2();	// WORD

// Fname (A faire ?)
ASTreeNode *fname();		// NAME [APPLY RULE 8]

// Simple_command
ASTreeNode *simple_command();	// test all posibilities
ASTreeNode *simple_command1();	// cmd_prefix, cmd_word, cmd_suffix
ASTreeNode *simple_command2();	// cmd_prefix, cmd_word
ASTreeNode *simple_command3();	// cmd_name, cmd_suffix
ASTreeNode *simple_command4();	// cmd_prefix
ASTreeNode *simple_command5();	// cmd_name

// Cmd_name
ASTreeNode *cmd_name();		// WORD [APPLY RULE 7a]

// Cmd_word
ASTreeNode *cmd_word();		// WORD [APPLY RULE 7b]

// Cmd_prefix
ASTreeNode *cmd_prefix();	// test all posibilities
ASTreeNode *cmd_prefix1();	// cmd_prefix, io_redirect
ASTreeNode *cmd_prefix2();	// cmd_prefix, ASSIGNEMENT_WORD
ASTreeNode *cmd_prefix3();	// io_redirect
ASTreeNode *cmd_prefix4();	// ASSIGNEMENT_WORD

// Cmd_suffix
ASTreeNode *cmd_suffix();	// test all posibilities
ASTreeNode *cmd_suffix1();	// cmd_suffix, io_redirect
ASTreeNode *cmd_suffix2();	// cmd_suffix, WORD
ASTreeNode *cmd_suffix3();	// io_redirect
ASTreeNode *cmd_suffix4();	// WORD

// Redirect_list
ASTreeNode *redirect_list();	// test all posibilities
ASTreeNode *redirect_list1();	// redirect_list, io_redirect
ASTreeNode *redirect_list2();	// redirect_list

// Io_redirect
ASTreeNode *io_redirect();	// test all posibilities
ASTreeNode *io_redirect1();	// IO_NUMBER, io_file
ASTreeNode *io_redirect2();	// IO_NUMBER, io_here
ASTreeNode *io_redirect3();	// io_file
ASTreeNode *io_redirect4();	// io_here

// Io_file 
ASTreeNode *io_file();		// test all posibilities
ASTreeNode *io_file1();		// '<'
ASTreeNode *io_file2();		// LESSAND (aka '<&')
ASTreeNode *io_file3();		// '>'
ASTreeNode *io_file4();		// GREATAND (aka '>&')
ASTreeNode *io_file5();		// DGREAT (aka '>>')
ASTreeNode *io_file6();		// LESSGREAT (aka '<>')
ASTreeNode *io_file7();		// CLOBBER (aka '>|')

// Filename
ASTreeNode *filename();		// WORD [APPLY RULE 2]

// Io_here
ASTreeNode *io_here();		// test all posibilities
ASTreeNode *io_here1();		// DLESS, here_end
ASTreeNode *io_here2();		// DLESSDASH here_end

// Here_end
ASTreeNode *here_end();		// WORD [APPLY RULE 3]

// Newline_list
ASTreeNode *newline_list();	// test all posibilities
ASTreeNode *newline_list1();	// newline_list, NEWLINE
ASTreeNode *newline_list2();	// NEWLINE

//Linebreak
ASTreeNode *linebreak();	// test all posibilities
ASTreeNode *linebreak1();	// newline_list
ASTreeNode *linebreak2();	// EMPTY

// Separator_op
ASTreeNode *seperator_op();	// test all posibilities
ASTreeNode *separator_op1();	// '&'
ASTreeNode *separator_op2();	// ';'

// Separator
ASTreeNode *separator();	// test all posibilities
ASTreeNode *separator1();	// separator_op, linebreak
ASTreeNode *separator2();	// newline_list

// Sequential_sep
ASTreeNode *sequential_sep();	// test all positibilities
ASTreeNode *sequential_sep1();	// ';', linebreak
ASTreeNode *sequential_sep2();	// newline_list
*/

int	ft_parse(t_lex **lex, t_ast **ast)
{
	t_lex	*current;

	current = *lex;
	*ast = program(current);
	if (g_shell->lex_size == 0)
		return (-1);
	return (1);
}
