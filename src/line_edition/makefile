# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frameton <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/03 23:49:06 by frameton          #+#    #+#              #
#    Updated: 2020/02/03 23:48:51 by frameton         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

FLAG	=	-Wall -Wextra -Werror -g

LIB	=	libft.a -ltermcap

SRC		=	main.c print_prompt.c get_command.c check_command.c exit.c\
			search_pathenv.c check_builtin.c init_builtin_ref.c\
			exec_builtin.c init_lst_env.c exec_command.c exec_unsetenv.c\
			exec_cd.c check_expansion.c check_auth.c init_lst.c\
			create_history.c get_next_line.c edit_history.c edit_line1.c\
			edit_line2.c edit_line3.c show_all_commands.c completion_commands.c\
			init_tab_path.c show_commands.c edit_line1_comp.c init_lst_comp.c\
			recup_stdin.c show_commands_tab.c show_commands_tab2.c\
			select_comp_tab.c select_comp_tab2.c select_comp_tab3.c\
			select_comp_tab4.c print_prompt2.c select_comp_tab5.c\
			del_char.c check_input_exist.c exec_setcpt.c exec_setcpt2.c\
			edl2_move_word.c write_lst.c cpc.c welcome.c ctrl_r.c print_lst.c\
			multiple_line.c outils_welcom.c outils_welcom2.c welcome2.c\
			welcome3.c coloration_completion.c exec_setcpt3.c\
			outils_edit_line1_comp.c edl1_move_word.c ctrl_r2.c op_paste.c\
			op_cut.c op_copy.c init_lst2.c init_lst3.c init_lst4.c\
			completion_commands2.c free_path_tab.c outils_completion.c\
			outils2_edit_line1_comp.c exec_help.c exec_help2.c exec_history.c\

OBJ		=	$(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)

	@make -C libft/
	@mv libft/libft.a .
	@gcc -o $(NAME) $(FLAG) $(OBJ) $(LIB)
	@echo "\033[1;32mDone.\033[0;m"

%.o: %.c
	@echo "\033[1;34mCompilation of $<...\033[0;m"
	@CC -I. -o $@ -c $? $(FLAG)

clean	:
			@rm -f $(OBJ)
			@echo "\033[0;31mDeleted object files.\033[0;m"

fclean	:	clean
			@rm -f $(NAME)
			@rm -f $(LIB)
			@echo "\033[0;31mDeleted $(NAME).\033[0;m"

re		:	fclean all
