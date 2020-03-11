/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linedition.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 01:07:38 by frameton          #+#    #+#             */
/*   Updated: 2020/03/11 19:45:17 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINEDITION_H
# define LINEDITION_H
# define FRED "\033[0;31m"
# define RED "\033[1;31m"
# define FGREEN "\033[0;32m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define FYELLOW "\033[0;33m"
# define BLUE "\033[1;34m"
# define FBLUE "\033[0;34m"
# define MAGENTA "\033[1;35m"
# define FMAGENTA "\033[0;35m"
# define CYAN "\033[1;36m"
# define GREY "\033[1;30m"
# define FCYAN "\033[0;36m"
# define WHITE "\033[0;m"
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
	int				lcl;
	struct s_lst2	*next;
}					t_lst2;

typedef struct		s_struct2
{
	char			*name;
	char			*cmd;
	char			*av;
	int				exs;
	int				reg;
	int				dir;
	int				chr;
	int				blk;
	int				fifo;
	int				lnk;
	int				sock;
	int				suid;
	int				sgid;
	int				stick;
	int				rd;
	int				wrt;
	int				exc;
	long long		sz;
}					t_struct2;

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

typedef struct		s_fc
{
	int				e;
	int				i;
	int				s;
	int				r;
	int				n;
	int				l;
	int				ret;
	int				min;
	int				frst;
	int				scd;
	int				max;
	char			*edtr;
	char			opt;
	t_htr			*h;
}					t_fc;

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
	int				iret;
	int				li;
	t_lst2			*env;
	int				prompt;
	int				exit;
	char			**builtin_ref;
	int				c;
	char			**av;
	char			**envi;
	char			*cpcl;
	char			*start_pwd;
	char			*cmd;
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
	int				set_cpt;
	int				eq;
	int				edq;
	int				bs;
	int				b;
	int				p;
	int				mp;
	int				env_i;
	int				cpt5;
	int				ctrl_d;
	int				copy;
	int				row;
	int				cpt_p2;
	int				cpt_p3;
	int				ret;
	int				cpt3;
	int				cpt_p;
	int				col;
	int				coprompt;
	int				cki;
	int				nl;
	t_htr			*com;
	t_htr			*bcom;
}					t_struct;

t_struct			*g_lined;

void				size_hanlder(int i);
void				catch_signal(void);
char				*search_pathenv(t_lst2 *env);
int					print_prompt(int p, t_struct *s, int i);
int					get_command(t_struct *s);
void				ft_exit(int i, t_struct *s);
int					check_command(char ***t, t_struct s, char *av, int c);
int					check_builtin(char *s, char **builtin, t_struct st);
void				tmp_free_struct(t_struct *s);
char				**init_builtin_ref(int c);
int					exec_builtin(t_struct *s, int c);
t_lst2				*init_lst_env(t_lst2 *l, char **env, t_lst2 *tmp, int c);
int					exec_command(t_struct *s, char **env);
int					exec_unsetenv(t_struct *s, char **av);
int					check_auth(char *s);
int					exec_setenv(t_struct *s, char **av, t_lst2 *new, int i);
int					exec_cd(t_struct *s, t_lst2 *tp, char *tmp, char *ocwd);
int					check_expansion(t_struct *s, int i, t_lst2 *env, int c);
int					create_path_home(t_struct *s, char *new, int i);
int					check_ls(t_struct *s);
int					init_lst(t_struct *s, int i, int r, int ret);
t_htr				*create_history(t_htr *h, t_htr *new, t_htr *bg
		, t_struct *s);
int					edit_history(t_htr **h, t_lst *l, t_lst *bg, t_htr *new);
int					edit_line3(t_struct *s, char buf[5]);
int					edit_line2(t_struct *s, t_lst **lbg, t_lst **tmp,
		char buf[5]);
int					edit_line(t_struct *s, char buf[5], int *i, t_htr **t);
int					del_move(int c);
char				**init_tab_path(char *s);
int					show_commands(char ***path, size_t c, t_htr *l, t_htr *bg);
int					ft_completion(t_struct *s, char **path, char buf[5], int i);
char				**init_tab_path2(char *s, t_struct *st);
int					s_command(struct dirent **dir_el, t_htr **l,
		t_htr **bg);
t_htr				*char_class(t_htr *l, t_htr *s);
void				free_completion_commands(t_htr **del, int i);
int					edit_line_comp(t_struct *s, char buf[5], int *i);
int					del_char1(char buf[5], t_struct *s, int *i);
int					init_lst_comp(char buf[5], t_struct *s, t_lst *l,
		t_lst *rt);
int					init_lst_2(t_struct *s, char buf[5], int *i,
		t_htr **t);
int					init_lst_3(t_struct *s, char buf[5], int c, t_lst *l);
int					init_lst_4(t_struct *s, char buf[5], int c, t_lst *l);
int					recup_stdin(t_struct *s, char buf[5], int *i, int ret);
int					create_line(char **line, t_struct *s, int i, int c);
int					s_command_tab(struct dirent **dir_el, t_comp **l,
		t_comp **bg, char *p);
t_comp				*char_class_tab(t_comp *l, t_comp *s);
void				print_comp_tab(t_comp *cmp, int c, int i, int *j);
t_comp				*attribute_col(int *co, t_comp *cmp);
int					find_next_cmp(t_comp *cmp, t_comp *tmp);
t_comp				*create_lst_comp_tab(char ***path, t_comp **bcmp,
		char *line, int i);
int					select_comp_tab(t_struct *s, t_comp *cmp, int i, int j);
void				left_touch(t_comp *cmp, t_comp *bcmp, int *j, int i);
void				up_touch(t_comp *cmp, t_comp *bcmp, int *j, int i);
void				down_touch(t_comp *cmp, t_comp *bcmp, int *j, int i);
int					other_touch(char buf[5], int *j, t_struct *s);
int					print_prompt_bis(int p, t_struct *s, int i);
int					check_input_exist(t_struct s, t_htr *com);
int					exec_setcpt(t_struct *s);
void				exec_setcpt6(t_struct *s, int m);
void				exec_setcpt2(t_struct *s, int m);
void				exec_setcpt3(t_struct *s, int m);
void				exec_setcpt7(t_struct *s);
void				exec_setcpt5(t_struct *s);
void				exec_setcpt4(t_struct *s);
int					exec_setcpt8(t_struct *s, int *m);
int					edl2_move_word(t_lst **lbg, t_lst **tmp, int c);
void				write_lst(t_struct *s, char buf[5], int *nl);
int					search_exec(char *s, char ***path, DIR *dir
		, struct dirent *dir_el);
void				es9(char *s, int m);
int					cpc(t_struct *s, char b, int i);
int					welcome(t_struct s);
void				fp(char *s, char *s2);
void				ft_putstr_anim(char *s, int c);
int					clr_cmp(t_comp *cmp, char *path);
int					ctrl_r(t_struct *s);
void				check_clr(t_comp *cmp);
int					print_lst(t_struct s, int *nl, int c);
void				set_pos_cur(t_struct *s, int i, int nl, int *pc);
void				ft_sleep(int i);
void				ft_vmarge(int m);
void				es8(int m, char *s);
void				bar(int m, int i);
void				rbar(int m);
void				cline(int m);
void				init_struct(t_struct *s, char **envp);
void				upl(int m);
void				fp(char *s, char *s2);
void				do_m(int m);
void				ft_putstr_anim(char *s, int c);
void				ps(char *s);
void				exit_edl(t_struct *s, char **cmd);
int					show_list_poss(t_struct *s);
int					no_match(t_struct s, t_comp *bcmp);
int					init_list_poss(t_struct *s, int *co, t_comp **cmp,
		t_comp **bcmp);
int					move_word(t_struct *s, int c);
int					change_lst(t_struct *s, t_htr *t, int c);
char				*new_l(char **l);
t_htr				*check_htr(t_htr *t, char *l);
int					op_paste(t_struct *s, char **l);
int					create_char(t_lst **end, char c);
int					free_sel(t_lst **bg, t_lst **end);
void				reset_sel(t_struct *s);
int					op_cut(t_struct *s, int i);
int					op_copy(t_struct *s, int i, char **l);
int					create_line(char **line, t_struct *s, int i, int c);
int					pwd_comp(struct dirent **dir_el, char *path, t_lst *l,
		int c);
t_htr				*create_lst_comp(char ***path, t_htr **bcom,
		char *line, t_lst *l);
char				*create_line_comp(char **line, t_htr *com, t_htr *bcom,
		int c);
void				check_part_comp2(t_struct *s, int i);
int					free_path(char ***path, int i);
void				free_bcom(t_struct *s);
int					rac_free_bcom(t_struct *s, int i);
void				welcome5_b(int m);
int					sec_free(char **s, int i);
int					putchar_completion(t_struct *s, t_htr **bcom, char **line,
		int c);
int					putchar_completion2(t_struct *s, char c);
t_htr				*create_lst_comp2(char ***del, char ***path);
int					count_lst_comp_tab(t_struct s);
int					ctrl_r2_b(char **l, char buf[5]);
int					exec_sethelp(void);
void				es7(char *s, int m);
void				exec_help2(int m);
int					exec_history(t_struct s);
int					history_exp(t_struct *s, int c, char *line);
void				free_lst(t_struct *s);
int					search_nbr_cmd(t_struct *s, char **line, char **tmp, int c);
int					no_match_cmd(t_struct *s);
int					change_lst_nbr(t_htr *t, t_struct *s);
int					search_str_cmd(t_struct *s, char **line, char **tmp, int c);
int					check_part_comp(t_struct *s, int i);
int					check_slash(t_struct *s, char **l);
int					check_quotes(t_struct *s, char buf[6]);
int					check_sign_edl1(t_struct *s, char buf[6]);
int					last_command(char **line, char **tmp, t_struct *s, int c);
int					ft_test(char **av, int ac, char *p);
int					check_op_3(t_struct2 *st);
int					check_op_4(char **av, int n1, int n2);
void				set_s(t_struct2 *st, struct stat s, char **p);
int					set_p_ac(char **p, char *av, t_struct2 *st);
int					check_path_cpt(t_struct *s, t_comp **cmp, t_comp **bcmp,
		char **l);
int					check_prec_path(struct stat *st, char **l, char **tmp,
		int *ind);
int					s_command_tab2(char *str, t_comp **l, t_comp **bg,
		char *p);
int					init_lst2_b4(char buf[701], t_lst **l, int *c);
int					e_cpt(t_struct *s, t_comp **cmp, t_comp **bcmp);
int					exec_env(t_struct *s);
int					exec_export(t_struct *s, char **av);
int					exec_set(t_struct *s, char **av);
int					exec_unset(t_struct *s, char **av);
int					exec_export5(char ***tmp, char **av, t_struct *s,
		t_lst2 **l);
void				free_tmp_export5(char ***tmp);
int					check_char_ctrl_r(char buf[5], int ret);
int					bsls(t_struct *s, char buf[701]);
void				check_bslash(char **save);
#endif
