/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 23:49:13 by frameton          #+#    #+#             */
/*   Updated: 2020/02/04 01:06:29 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define FRED "\033[0;31m"
# define FGREEN "\033[0;32m"
# define FYELLOW "\033[0;33m"
# define FBLUE "\033[0;34m"
# define MAGENTA "\033[1;35m"
# define FMAGENTA "\033[0;35m"
# define GREY "\033[1;30m"
# define FCYAN "\033[0;36m"
# define SCYAN "\033[0;30;46m"
# define SYELLOW "\033[0;30;43m"
# define SRED "\033[0;30;41m"
# define SGREEN "\033[0;30;42m"
# define BBLUE "\033[0;30;44m"
# define BMAGENTA "\033[0;30;45m"
# define BCYAN "\033[0;30;46m"
# define BWHITE "\033[0;30;47m"

# include "projectinclude.h"
# include <sys/types.h>
# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <pwd.h>
# include <unistd.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <grp.h>
# include <time.h>
# include <termcap.h>

# include <uuid/uuid.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <termios.h>
# include <signal.h>
# include <fcntl.h>

typedef struct		s_lst
{
	char			c;
	int				plc;
	int				line;
	int				sel;
	struct s_lst	*next;
	struct s_lst	*prev;
}					t_lst;

typedef struct		s_lst2
{
	char			*env;
	char			*varn;
	char			*var;
	int				nvar;
	int				nenv;
	int				size;
	struct s_lst2	*next;
}					t_lst2;

typedef struct		s_cpl
{
	char			*name;
	int				sz;
}					t_cpl;

typedef struct		s_htr
{
	char			*name;
	struct s_htr	*next;
	struct s_htr	*prev;
}					t_htr;

typedef struct		s_comp
{
	char			*name;
	struct s_comp	*next;
	struct s_comp	*begin;
	struct s_comp	*prev;
	struct s_comp	*end;
	struct s_comp	*pos_cur;
	int				cur;
	int				sel;
	int				pltc;
	int				col;
	int				co;
	int				li;
	int				clr;
}					t_comp;

typedef struct		s_struct
{
	int				li;
	t_lst2			*env;
	int				prompt;
	int				exit;
	char			**builtin_ref;
	int				c;
	char			**av;
	char			**envi;
	t_lst			*l;
	t_lst			*lbg;
	t_lst			*tmp;
	pid_t			first;
	char			*env_path;
	DIR				*dir;
	struct dirent	*dir_el;
	int				t;
	t_htr			*h;
	t_cpl			comp;
	int				cpt;
	int				cpt3;
	char			*cpcl;
	int				set_cpt;
	int				mp;
	int				row;
	int				col;
	int				coprompt;
	int				cki;
	int				nl;
	t_htr			*com;
	t_htr			*bcom;
	int				iret;
}					t_struct;

/*
********************************************************************************
*/

/*
** check_auth.c
*/
int					check_auth(char *s);
int					check_ls(t_struct *s);

/*
** check_builtin.c
*/
int					check_builtin(char *s, char **builtin, t_struct st);

/*
** check_command.c
*/
int					free_tab_path(char ***tab, int c);
int					search_exec(
	char *s, char ***path, DIR *dir, struct dirent *dir_el);
char				**create_path_tab(char *s, char **path);
char				**init_tab_path(char *s);
int					check_command(char ***t, t_struct s, char *av, int c);

/*
** check_expansion.c
*/
char				*change_string2(char *bg, char *t, char *var, int c);
int					change_string(
	char **bg, char *t, t_struct s, size_t c);
int					check_expansion3(char **bg, char *t);
int					check_expansion2(t_struct *s, int i);
int					check_expansion(
	t_struct *s, int i, t_lst2 *env, int c);

/*
** check_input_exist.c
*/
int					check_input_exist2(t_struct *s, int *i, int *c);
int					check_input_exist3(
	t_struct s, int c, int i, t_htr *com);
int					check_input_exist(t_struct s, t_htr *com);

/*
** coloration_completion.c
*/
int					check_executable(struct stat s);
void				check_clr(t_comp *cmp);
int					clr_cmp(t_comp *cmp, char *path);

/*
** completion_commands.c
*/
void				free_bcom(t_struct *s);
int					putchar_completion2(t_struct *s, char c);
int					completion_commands(
	char ***path, int c, t_struct *s, int i);
int					ft_completion(
	t_struct *s, char **path, char buf[5], int i);

/*
** completion_commands2.c
*/
int					create_line(char **line, t_struct *s, int i, int c);
int					pwd_comp(
	struct dirent **dir_el, char *path, t_lst *l, int c);
t_htr				*create_lst_comp(
	char ***path, t_htr **bcom, char *line, t_lst *l);
char				*create_line_comp(
	char **line, t_htr *com, t_htr *bcom, int c);
void				check_part_comp2(t_struct *s, int i);

/*
** cpc.c
*/
void				reset_sel(t_struct *s);
int					free_sel(t_lst **bg, t_lst **end);
int					create_char(t_lst **end, char c);
int					cpc(t_struct *s, char b, int i);

/*
** create_history.c
*/
t_htr				*create_history(
	t_htr *h, t_htr *new, t_htr *bg, t_struct *s);

/*
** ctrl_r.c
*/
int					ctrl_r(t_struct *s);

/*
** ctrl_r2.c
*/
t_htr				*check_htr(t_htr *t, char *l);
char				*new_l(char **l);
int					ctrl_r2_b(char **l, char buf[5]);
int					change_lst(t_struct *s, t_htr *t, int c);

/*
** del_char.c
*/
int					del_char(char buf[5], t_struct *s, int *i);

/*
** edit_history.c
*/
int					edit_history(
	t_htr **h, t_lst *l, t_lst *bg, t_htr *new);

/*
** edit_line1.c
*/
int					edit_line(t_struct *s, char buf[5], int *i, t_htr **t);

/*
** edit_line1_comp.c
*/
int					init_list_poss(
	t_struct *s, int *co, t_comp **cmp, t_comp **bcmp);
int					no_match(t_struct s, t_comp *bcmp);
int					edit_line_comp(t_struct *s, char buf[5], int *i);

/*
** edit_line2.c
*/
int					edit_line2(t_lst **lbg, t_lst **tmp, char buf[5]);

/*
** edit_line3.c
*/
int					del_move(int c);
int					edit_line3(t_struct *s, char buf[5]);

/*
** edl1_move_word.c
*/
int					move_word(t_struct *s, int c);

/*
** edl2_move_word.c
*/
int					move_word_r_w(t_lst **tmp);
int					move_word_r(t_lst **tmp);
int					edl2_move_word_w(t_lst **lbg, t_lst **tmp);
int					edl2_move_word(t_lst **lbg, t_lst **tmp, int c);

/*
** exec_builtin.c
*/
int					checkenv_setenv(t_struct s, t_lst2 *l, int i, int c);
t_lst2				*exec_setenv2(
	t_lst2 *l, char *s, int c, t_struct *st);
int					exec_setenv(t_struct *s);
int					exec_builtin2(t_struct *s, int c);
int					exec_builtin(t_struct *s, int c);

/*
** exec_cd.c
*/
char				*mini_strjoin(char *s1, char *s2);
int					create_path_home(t_struct *s, char *new, int i);
int					exec_cd2(
	t_struct *s, char *cwd, char *ocwd, char *tmp);
char				**modif_av(char ***av);
int					exec_cd(
	t_struct *s, t_lst2 *tp, char *tmp, char *ocwd);

/*
** exec_command.c
*/
int					exec_command(t_struct *s, char **env);

/*
** exec_help.c
*/
void				es7(char *s, int m);
int					exec_sethelp(void);

/*
** exec_help2.c
*/
int					exit_sethelp(struct termios *term);
void				exec_help2(int m);

/*
** exec_history.c
*/
int					exec_history(t_struct s);

/*
** exec_setcpt.c
*/
void				exec_setcpt3(t_struct *s, int m);
void				write_anim(int i);
void				anim_cpt(int m, int lr, int c, int i);
int					exec_setcpt(t_struct *s);

/*
** exec_setcpt2.c
*/
void				es9(char *s, int m);
int					exec_setcpt8(
	t_struct *s, struct termios *term, int *m);
void				exec_setcpt6(t_struct *s, int m);
void				exec_setcpt7(t_struct *s);

/*
** exec_setcpt3.c
*/
void				exec_setcpt2(t_struct *s, int m);
void				exec_setcpt4(t_struct *s);
void				exec_setcpt5(t_struct *s);

/*
** exec_unsetenv.c
*/
int					exec_unsetenv(t_struct *s);

/*
** exit.c
*/
void				ft_exit(int i, t_struct *s);

/*
** free_path_tab.c
*/
int					free_path(char ***path, int i);
int					rac_free_bcom(t_struct *s, int i);

/*
** get_command.c
*/
int					get_command(t_struct *s);

/*
** get_next_line.c
*/
void				ft_list_clear(t_gnl **begin_list, int ind);
int					ft_list_size(t_gnl *begin_list, int c);
t_gnl				*ft_lst_new(char c, t_gnl **lst, t_gnl *sa, int fd);
int					get_next_line(const int fd, char **line);

/*
** init_builtin_ref.c
*/
char				**init_builtin_ref2(int c, char **builtin);
char				**init_builtin_ref(int c);

/*
** init_lst.c
*/
int					init_lst(t_struct *s, int i, int r, int ret);

/*
** init_lst2.c
*/
int					init_lst_2(
	t_struct *s, char buf[5], int *i, t_htr **t);

/*
** init_lst3.c
*/
int					init_lst_3(t_struct *s, char buf[5], int c, t_lst *l);

/*
** init_lst4.c
*/
int					init_lst_4(t_struct *s, char buf[5], int c, t_lst *l);

/*
** init_lst_comp.c
*/
int					init_lst_comp(
	char buf[5], t_struct *s, t_lst *l, t_lst *rt);

/*
** init_lst_env.c
*/
t_lst2				*init_lst_env(
	t_lst2 *l, char **env, t_lst2 *tmp, int c);

/*
** init_lsttt.c
*/
int					init_lst(t_struct *s, int i, int r, int ret);

/*
** init_tab_path.c
*/
char				**init_tab_path2(char *s);

/*
** main.c
*/
int					main(int ac, char **av, char **envp);

/*
** multiple_line.c
*/
void				set_pos_cur(t_struct *s, int i, int nl, int *pc);

/*
** op_copy.c
*/
int					op_copy(t_struct *s, int i, char **l);

/*
** op_cut.c
*/
int					op_cut(t_struct *s, int i);

/*
** op_paste.c
*/
int					op_paste(t_struct *s, char **l);

/*
** outils2_edit_line1_comp.c
*/
int					count_lst_comp_tab(t_struct s);

/*
** outils_completion.c
*/
t_htr				*create_lst_comp2(char ***del, char ***path);
int					sec_free(char **s, int i);
int					putchar_completion(
	t_struct *s, t_htr **bcom, char **line, int c);

/*
** outils_edit_line1_comp.c
*/
int					free_bcmp_tab(t_comp **bcmp, t_comp **cmp, int i);
int					show_list_poss(t_struct *s);

/*
** outils_welcom.c
*/
void				ft_sleep(int i);
void				ft_vmarge(int m);
void				es8(int m, char *s);
void				bar(int m, int i);
void				rbar(int m);

/*
** outils_welcom2.c
*/
void				cline(int m);
void				upl(int m);
void				fp(char *s, char *s2);
void				do_m(int m);
void				ft_putstr_anim(char *s, int c);

/*
** print_lst.c
*/
void				write_lst3(int *c, t_struct s, int *i, int *nl);
int					print_lst(t_struct s, int *nl, int c);

/*
** print_prompt.c
*/
int					lst2_size(t_lst2 *l);
int					print_prompt(int p, t_struct *s, int i);

/*
** print_prompt2.c
*/
int					print_prompt_bis(int p, t_struct *s, int i);

/*
** recup_stdin.c
*/
int					recup_stdin(t_struct *s, char buf[5], int *i, int ret);

/*
** search_pathenv.c
*/
char				*search_pathenv(t_lst2 *l);

/*
** select_comp_tab.c
*/
int					tab_touch(t_comp *cmp, t_comp *bcmp, int *j, int i);
int					entr_touch2(t_struct *s, char *line, t_lst *l);
int					entr_touch(t_comp *cmp, t_struct *s, int *j, int c);
int					select_comp_tab(
	t_struct *s, t_comp *cmp, int i, int j);

/*
** select_comp_tab2.c
*/
void				left_touch2(t_comp *end, int c, int *j, t_comp **cmp);
void				left_touch(t_comp *cmp, t_comp *bcmp, int *j, int i);

/*
** select_comp_tab3.c
*/
void				up_touch2(t_comp **cmp, t_comp *bcmp, int c);
void				up_touch(t_comp *cmp, t_comp *bcmp, int *j, int i);

/*
** select_comp_tab4.c
*/
void				down_touch2(t_comp **cmp, t_comp *bcmp, int c);
void				down_touch(t_comp *cmp, t_comp *bcmp, int *j, int i);

/*
** select_comp_tab5.c
*/
int					other_touch(char buf[5], int *j, t_struct *s);

/*
** show_all_commands.c
*/
int					show_commands(
	char ***path, size_t c, t_htr *l, t_htr *bg);

/*
** show_commands.c
*/
t_htr				*char_class(t_htr *l, t_htr *s);
void				free_completion_commands(t_htr **del, int i);
int					s_command3(
	t_htr **l, t_htr **bg, struct dirent **dir_el);
int					s_command(
	struct dirent **dir_el, t_htr **l, t_htr **bg);

/*
** show_commands_tab.c
*/
t_comp				*char_class_tab(t_comp *l, t_comp *s);
int					s_command_tab(
	struct dirent **dir_el, t_comp **l, t_comp **bg, char *p);

/*
** show_commands_tab2.c
*/
t_comp				*create_lst_comp_tab(
	char ***path, t_comp **bcmp, char *line, int i);
int					find_next_cmp(t_comp *cmp, t_comp *tmp);
t_comp				*attribute_col(int *co, t_comp *cmp);
void				print_comp_tab(t_comp *cmp, int c, int i, int *j);

/*
** welcome.c
*/
void				ps(char *s);
int					welcome(t_struct s);

/*
** welcome2.c
*/
void				welcome5(int m);
void				welcome6(int m);
void				welcome7(int m);
void				welcome8(int m);
void				welcome9(int m);

/*
** welcome3.c
*/
void				welcome5_b(int m);
int					welcome10(int m, t_struct s);

/*
** write_lst.c
*/
void				write_lst(t_struct *s, char buf[5], int *nl);

#endif
