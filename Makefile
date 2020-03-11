# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/13 18:51:58 by mabayle           #+#    #+#              #
#    Updated: 2020/03/11 16:06:09 by ymarcill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	42sh

CC			:=	clang
LINKER		:=	clang -o

DEBUG		:=	0

LIBFT		:=	libft/libft.a

INCLUDES	:=	./includes

INCS		=	./includes/get_next_line.h \
				./includes/grammar.h \
				./includes/jobcontrol.h \
				./includes/lexer.h \
				./includes/linedition.h \
				./includes/mybtree.h \
				./includes/parser.h \
				./includes/input.h \
				./includes/projectinclude.h

#libft
INCLUDES	:=	$(INCLUDES) -I$(dir $(LIBFT))includes
LDFLAGS		:=	-L$(dir $(LIBFT)) -lft -fsanitize=address

CFLAGS		:=	-Wall -Wextra -Werror -I$(INCLUDES) -g3 -fsanitize=address
ifeq ($(DEBUG), 1)
	CFLAGS	:=	$(CFLAGS) -ggdb -fno-omit-frame-pointer -fsanitize=address
endif

SRC_PATH	:=	./src/
OBJ_PATH	:=	./obj/

SRC		:=	main.c \
			builtins/type.c\
			builtins/hash.c\
			builtins/alias.c\
			builtins/alias_bis.c\
			builtins/unalias.c\
			jobcontrol/init_interactive_shell.c \
			jobcontrol/put_in_fg.c \
			jobcontrol/ft_job.c\
			jobcontrol/ft_job_bis.c\
			jobcontrol/job_fill_exec.c\
			jobcontrol/manage_job.c\
			jobcontrol/find_right_job.c\
			jobcontrol/manage_job_list.c\
			jobcontrol/put_in_bg.c \
			jobcontrol/changed_status.c \
			jobcontrol/job_alloc.c \
			execution/pipeline_exec.c \
			execution/simple_exec.c \
			execution/process_fd.c \
			execution/browse_ast.c \
			execution/exec_ast.c\
			execution/pipeline_ast.c \
			execution/get_path.c \
			execution/assign.c\
			execution/assign_bis.c\
			execution/child_exec.c\
			utils/ft_freetab.c\
			utils/tab_utils.c\
			utils/ft_strdupn.c\
			utils/ft_strlenu.c\
			redirections/redirect_to_fd.c \
			redirections/redir_utils.c \
			redirections/exec_redir.c \
			redirections/parse_redir.c \
			redirections/heredoc.c \
			lexer/lexer.c \
			lexer/list_utils.c \
			lexer/utils.c \
			lexer/type_token.c \
			lexer/print_debug.c \
			parser/parser.c \
			parser/grammar/and_or.c \
			parser/grammar/cmd_name.c \
			parser/grammar/cmd_prefix.c \
			parser/grammar/cmd_suffix.c \
			parser/grammar/cmd_word.c \
			parser/grammar/complete_cmd.c \
			parser/grammar/complete_cmds.c \
			parser/grammar/filename.c \
			parser/grammar/here_end.c \
			parser/grammar/io_file.c \
			parser/grammar/io_here.c \
			parser/grammar/io_redirect.c \
			parser/grammar/linebreak.c \
			parser/grammar/list_grammar.c \
			parser/grammar/newline_list.c \
			parser/grammar/pipe_sequence.c \
			parser/grammar/pipeline.c \
			parser/grammar/program.c \
			parser/grammar/separator_op.c \
			parser/grammar/separator.c \
			parser/grammar/simple_command.c \
			ast/ast.c \
			ast/process_ast.c \
			ast/print_ast.c \
			ast/ast_utils.c \
			line_edition/check_auth.c \
			line_edition/check_builtin.c \
			line_edition/check_command.c \
			line_edition/check_expansion.c \
			line_edition/check_input_exist.c \
			line_edition/coloration_completion.c \
			line_edition/completion_commands.c \
			line_edition/completion_commands2.c \
			line_edition/cpc.c \
			line_edition/create_history.c \
			line_edition/ctrl_r.c \
			line_edition/ctrl_r2.c \
			line_edition/del_char.c \
			line_edition/edit_history.c \
			line_edition/edit_line1.c \
			line_edition/edit_line1_comp.c \
			line_edition/edit_line1_comp2.c \
			line_edition/edit_line2.c \
			line_edition/edit_line3.c \
			line_edition/edl1_move_word.c \
			line_edition/edl2_move_word.c \
			line_edition/exec_command.c \
			line_edition/exec_help.c \
			line_edition/exec_cd.c \
			line_edition/exec_help2.c \
			line_edition/exec_history.c \
			line_edition/exec_setcpt.c \
			line_edition/exec_setcpt2.c \
			line_edition/exec_setcpt3.c \
			line_edition/exec_unsetenv.c \
			line_edition/exit.c \
			line_edition/free_path_tab.c \
			line_edition/get_command.c \
			line_edition/get_next_line.c \
			line_edition/init_builtin_ref.c \
			line_edition/init_lst.c \
			line_edition/init_lst2.c \
			line_edition/init_lst3.c \
			line_edition/init_lst4.c \
			line_edition/init_lst_comp.c \
			line_edition/init_lst_env.c \
			line_edition/init_tab_path.c \
			line_edition/multiple_line.c \
			line_edition/op_copy.c \
			line_edition/op_cut.c \
			line_edition/op_paste.c \
			line_edition/outils2_edit_line1_comp.c \
			line_edition/outils_completion.c \
			line_edition/outils_edit_line1_comp.c \
			line_edition/outils_welcom.c \
			line_edition/outils_welcom2.c \
			line_edition/print_lst.c \
			line_edition/print_prompt.c \
			line_edition/print_prompt2.c \
			line_edition/recup_stdin.c \
			line_edition/search_pathenv.c \
			line_edition/search_nbr_cmd.c \
			line_edition/select_comp_tab.c \
			line_edition/select_comp_tab2.c \
			line_edition/select_comp_tab3.c \
			line_edition/select_comp_tab4.c \
			line_edition/select_comp_tab5.c \
			line_edition/show_all_commands.c \
			line_edition/show_commands.c \
			line_edition/show_commands_tab.c \
			line_edition/show_commands_tab2.c \
			line_edition/welcome.c \
			line_edition/write_lst.c \
			line_edition/check_quotes.c \
			line_edition/history_exp.c \
			line_edition/search_str_cmd.c \
			line_edition/exit_edl.c\
			line_edition/test.c\
			line_edition/test2.c\
			line_edition/test3.c\
			line_edition/test4.c\
			line_edition/show_commands_tab3.c\
			line_edition/init_lst2_b.c\
			line_edition/exec_setenv.c\
			line_edition/exec_env.c\
			line_edition/exec_export.c\
			line_edition/exec_set.c\
			line_edition/exec_unset.c\
			input/line_edition.c \
			input/term_mode.c \
			input/get_cursor_pos.c \
			input/move_cursor.c \
			input/go_last_char.c \
			input/right_arrow.c \
			input/insert_del.c \
			input/move_toword.c \
			input/ft_copy_cut_paste_del.c \
			input/char_handler.c \
			input/tools.c \
			input/tools_bis.c \
			input/signals.c 

OBJ		:=	$(addprefix $(OBJ_PATH), $(SRC:.c=.o))
SRC		:=	$(addprefix $(SRC_PATH), $(SRC))

all:
	@python3 .header.py
	@make $(NAME)

$(NAME):  $(LIBFT) $(OBJ)
	@$(LINKER) $(NAME) $(LDFLAGS) $(OBJ) -ltermcap -fsanitize=address
	@echo ""
	@echo "\033[0;32m42sh build done\033[0m"
	@echo ""
	@cp -R ./.builtin_name ~/

$(LIBFT):	$(dir $(LIBFT))Makefile
	@make -j4 -C $(dir $(LIBFT))

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INCS)
	@echo "\033[0;32m[✓]\033[0m\033[0;33m [42sh] Compiling : \033[0m" $<
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -j4 -C libft/ clean
	@rm -rf $(OBJ_PATH)
	@echo "\033[0;32m[✓]\033[0m\033[0;33m [42sh] Deleted all .o\033[0m"
	@rm -rf 42sh.dSYM
	@rm -rf ~/.builtin_name

fclean:
	@make -j4 -C libft/ fclean
	@rm -f $(NAME)
	@rm -rf $(OBJ_PATH)
	@echo "\033[0;32m[✓]\033[0m\033[0;33m [42sh] Deleted all .o\033[0m"
	@echo "\033[0;32m[✓]\033[0m\033[0;33m [42sh] Deleted 42sh\033[0m"

re: fclean all

.PHONY:	all clean fclean re
