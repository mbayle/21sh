# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/13 18:51:58 by mabayle           #+#    #+#              #
#    Updated: 2020/02/03 06:03:09 by mabayle          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	21sh

CC			:=	gcc
LINKER		:=	gcc -o

DEBUG		:=	0

LIBFT		:=	libft/libft.a

INCLUDES	:=	./includes

#libft
INCLUDES	:=	$(INCLUDES) -I$(dir $(LIBFT))includes
LDFLAGS		:=	-L$(dir $(LIBFT)) -lft

CFLAGS		:=	-Wall -Wextra -Werror -g3 -I$(INCLUDES)

ifeq ($(DEBUG), 1)
	CFLAGS	:=	$(CFLAGS) -fsanitize=address -ggdb -fno-omit-frame-pointer
endif

SRC_PATH	:=	./src/
OBJ_PATH	:=	./obj/

SRC		:=	main.c \
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
			line_edition/print_prompt.c \
			line_edition/get_command.c \
			line_edition/check_command.c \
			line_edition/exit.c \
			line_edition/search_pathenv.c \
			line_edition/check_builtin.c \
			line_edition/init_builtin_ref.c \
			line_edition/exec_builtin.c \
			line_edition/init_lst_env.c \
			line_edition/exec_command.c \
			line_edition/exec_unsetenv.c \
			line_edition/exec_cd.c \
			line_edition/check_expansion.c \
			line_edition/check_auth.c \
			line_edition/init_lst.c \
			line_edition/create_history.c \
			line_edition/edit_history.c \
			line_edition/edit_line1.c \
			line_edition/edit_line2.c \
			line_edition/edit_line3.c \
			line_edition/show_all_commands.c \
			line_edition/completion_commands.c \
			line_edition/init_tab_path.c \
			line_edition/show_commands.c \
			line_edition/edit_line1_comp.c \
			line_edition/init_lst_comp.c \
			line_edition/recup_stdin.c \
			line_edition/show_commands_tab.c \
			line_edition/show_commands_tab2.c \
			line_edition/select_comp_tab.c \
			line_edition/select_comp_tab2.c \
			line_edition/select_comp_tab3.c \
			line_edition/select_comp_tab4.c \
			line_edition/print_prompt2.c \
			line_edition/select_comp_tab5.c \
			line_edition/del_char.c \
			line_edition/check_input_exist.c \
			line_edition/exec_setcpt.c \
			line_edition/exec_setcpt2.c \
			line_edition/edl2_move_word.c \
			line_edition/write_lst.c \
			line_edition/cpc.c \
			line_edition/welcome.c \
			line_edition/ctrl_r.c \
			line_edition/print_lst.c \
			line_edition/multiple_line.c \
			line_edition/outils_welcom.c \
			line_edition/outils_welcom2.c \
			line_edition/welcome2.c \
			line_edition/welcome3.c \
			line_edition/coloration_completion.c \
			line_edition/exec_setcpt3.c \
			line_edition/outils_edit_line1_comp.c \
			line_edition/edl1_move_word.c \
			line_edition/ctrl_r2.c \
			line_edition/op_paste.c \
			line_edition/op_cut.c \
			line_edition/op_copy.c \
			line_edition/init_lst2.c \
			line_edition/init_lst3.c \
			line_edition/init_lst4.c \
			line_edition/completion_commands2.c \
			line_edition/free_path_tab.c

OBJ		:=	$(addprefix $(OBJ_PATH), $(SRC:.c=.o))
SRC		:=	$(addprefix $(SRC_PATH), $(SRC))

all:
	@python3 .header.py
	@make $(NAME)

$(NAME):  $(LIBFT) $(OBJ)
	@$(LINKER) $(NAME) $(LDFLAGS) $(OBJ) -ltermcap
	@echo ""
	@echo "\033[0;32m 21sh build done \033[0m"
	@echo ""

$(LIBFT):	$(dir $(LIBFT))Makefile
	@make -C $(dir $(LIBFT))

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INCS)
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m [21_SH] Compiling : \033[0m" $<
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C libft/ clean
	@rm -rf $(OBJ_PATH)
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m [21_SH] Deleted all .o\033[0m"

fclean:
	@make -C libft/ fclean
	@rm -f $(NAME)
	@rm -rf $(OBJ_PATH)
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m [21_SH] Deleted all .o\033[0m"
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m [21_SH] Deleted 21sh\033[0m"

re: fclean all

.PHONY:	all clean fclean re
