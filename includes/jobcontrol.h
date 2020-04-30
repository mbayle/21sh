/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 11:30:26 by ymarcill          #+#    #+#             */
/*   Updated: 2020/04/29 19:20:47 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBCONTROL_H
# define JOBCONTROL_H

# include "projectinclude.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/errno.h>
# include <dirent.h>
# include "lexer.h"
# include "linedition.h"

typedef struct			s_myenv
{
	char				*key;
	char				*val;
	char				*keyval;
	struct s_myenv		*next;
}						t_myenv;

typedef struct			s_myloc
{
	char				*key;
	char				*val;
	char				*keyval;
	struct s_myloc		*next;
}						t_myloc;

/*
** a process is a single process
*/

typedef struct			s_process
{
	struct s_process	*next;
	char				*cmd;
	int					bin;
	pid_t				lpid;
	int					status;
	int					r_value;
	int					my_stdin;
	int					my_stdout;
	int					p_nb;
}						t_process;

/*
** a job is a pipeline of process
*/

typedef struct			s_job
{
	struct s_process	*first_process;
	struct termios		j_mode;
	struct s_job		*next;
	char				*command;
	int					fg;
	int					j_nb;
	int					stop;
	int					completed;
	pid_t				pgid;
	int					last_j;
	int					last_ret;
}						t_job;

typedef struct			s_hash
{
	char				*path;
	int					hits;
	struct s_hash		*next[256];
}						t_hash;

typedef struct			s_alias
{
	char				*key;
	char				*value;
	struct s_alias		*next;
}						t_alias;

typedef struct			s_jobcontrol
{
	char				***arg;
	char				**env;
	char				**av;
	char				**ass_stock;
	char				**ass_stockenv;
	char				**ass;
	char				*mypath;
	char				*heredoc;
	t_hash				*h_tab;
	t_myenv				*myenv;
	t_myloc				*myloc;
	struct termios		term_attr;
	struct termios		save_attr;
	struct s_job		*first_job;
	struct s_job		*first_mail;
	struct s_alias		*alias;
	pid_t				shell_pgid;
	int					shell_is_int;
	int					repere;
	int					ret;
	int					i;
	int					cm;
	int					stdi;
	int					stdo;
	int					stde;
	int					g_fg;
	int					assi;
	int					red;
	int					ao;
	int					sim;
	t_struct			s;
	int					here;
	int					index;
	int					f;
	int					perm;
	int					nv;
	int					stopexe;
	int					fils;
	int					p;
}						t_jobcontrol;

typedef struct			s_read
{
	DIR					*ptr;
	struct dirent		*file;
	struct stat			rdbuf;
	char				*path;
	char				*tmp;

}						t_read;

typedef	struct			s_index
{
	int					i;
	int					j;
	int					x;
	int					y;
	char				**command;
}						t_index;

struct s_jobcontrol		g_jobcontrol;

/*
** env
*/
void					add_env_bis(char *keyval, char **tmp);
void					add_loc_bis(char *keyval, char **tmp);
void					replace_env_bis(char *keyval, char **tmp, t_myenv *env);
void					replace_loc_bis(char *keyval, char **tmp, t_myloc *loc);
int						mypwd(void);
char					*get_myenv(char *key);
char					**set_copy(t_myloc *loc);
void					fill_struct_env(void);
int						delete_loc(char *keyval);
int						delete_env(char *keyval);
int						replace_loc(char *keyval);
int						add_loc(char *keyval);
int						check_env(char *keyval);
int						check_loc(char *keyval);
int						replace_env(char *keyval, int ass);
int						add_env(char *keyval, int ass);
int						myexport(char **cmd);
int						myenv(void);
int						myset(char **cmd);
int						unsetloc(char **cmd);
int						myunsetenv(char **cmd);
int						check_error(char *keyval);
int						setloc(char **cmd);
int						mysetenv(char **cmd, int ass);

/*
** assign
*/

char					*fill_keyval(char *ass);
void					save_ass(char **ass);
int						fill_tab_stock_env(char *ass, int y);
char					**cpy_env_plus(char **ass);
void					unexec_ass(char **ass);
char					**del_one(char **tabl, int pos);
int						just_ass(char **ass);
void					exec_ass(char **ass, int env);
char					**get_key(char **ass);
char					**move_char(char **ass);

/*
** expansion
*/

int						between_q(char *str);
char					**ft_command_to_args(char **args);
char					*check_exp_hashper(char *exp, char c);
char					*simple_hash_word(char *exp, char c);
char					*simple_hash(char *exp, char c);
char					*simple_exp(char *exp);
char					**get_param_word(char *exp, char c);
char					*check_match(char *param, char *word, char c);

/*
** builtuin
*/

int						exec_hash(t_hash **hash, char *pathvar, char **cmd);
int						hash_add(t_hash **hash, char *pathvar, char **cmd);
int						hash_not_found(char *cmd);
int						hash_invalid_opt(char opt);
void					print_hash(t_hash *hash);
void					rec_print_hash(t_hash *hash);
t_hash					*add_command(char *command,
						char *pathvar, t_hash **hash);
t_hash					*browse_command(char *command,
						char *pathvar, t_hash **hash);
void					free_pathlisr(char **pathlist);
char					*browse_command_path(char *command, char **pathlist);
void					hash_reset(t_hash **hash);
t_hash					*new_hash_entry(char *command,
						char *path, t_hash **hash);
t_hash					*new_hash_page(void);
t_hash					*attempt_hit(char *command, t_hash *hash);
char					**getpathlist(char *pathvar);
char					*getpathvar(char **envp);
void					malloc_exit(void);
int						check_b(char **cmd);
int						exec_echo(char **cmd);
void					hash_reset(t_hash **hash);
int						exec_hash(t_hash **hash, char *pathvar, char **cmd);
t_hash					*browse_command(char *command,
						char *pathvar, t_hash **hash);
void					alloc_alias(void);
t_alias					*set_value(t_alias *al, char *key, char *value);
t_alias					*set_alias(t_alias *al, char *key, char *value);
int						check_error_key(char *cmd);
char					**key_val_split(char *cmd);
int						exec_type(char **arg);
int						exec_alias(char **cmd);
int						exec_unalias(char **cmd);

/*
** redir
*/

char					**lex_to_tab(t_lex *lex);
int						myheredoc(char *redir, char *file, int nb);
void					nb_heredoc(char **cmd);
int						lex_size(t_lex *lex);
int						check_fd(int fd, int n);
int						size_tab(char *line);
int						ft_seq_occur(char *str, char *seq);
int						dig_to_io(char *str);
int						is_strdigit(char *str);
int						if_digit(char *file, int n);
int						dup_fd(char *redir, char *file);
int						out_err_redir(char *file);
int						redir_to_file(char **cmd, int i, int ret);
int						ie(char *str);
int						execute_redir(char **cmd);
int						redirect_to_file(char *redir, char *file,
						mode_t mode, int stfd);
int						dig_to_io(char *str);

/*
**parse ast
*/

char					**parse_redir(char **line, int exec);

/*
** Utils
*/

size_t					number_size(int n);
int						elst_size(t_myloc *menv);
char					**check_opt_env(char **cmd);
int						is_env_arg(char **cmd);
char					**env_copy(t_myenv *menv);
void					unexec_asign(void);
int						should_i_exec(char **cmd, char *mypath,
						int oldlink[2], int newlink[2]);
char					*concat_tab(char **tmp);
char					**copy_u(char **cmd, int pos);
char					*ft_strdupt(char *str, char c);
char					**del_one(char **tabl, int pos);
int						just_ass(char **ass);
void					ft_printtab(char **tt);
int						reset_attr();
int						ft_occur(char const *s, char c);
char					*ft_strjoinnf(char const *s1, char const *s2);
char					*ft_strjoinfree(char *s1, char *s2);
int						ft_strlenu(char *str);
char					**quick_tab_cmd(char *line);
int						permissions(char **str);
char					*ft_strdupn(char *str, char c);
char					*ft_strldup(char *str, char c);

/*
** Manage job list
*/

void					if_stp(t_job *job, int i);
t_job					*print_and_del(t_job *job, int i, int check);
t_job					*check_bg_status(t_job *job);
void					status_builtin(t_process *pro);
void					browse_process(t_process *pro, t_job *cpy);
void					delete_process(t_process *pro);
void					delete_job(t_job *job);
t_job					*delete_first(t_job *first);
t_job					*delete_link(pid_t pgid);
int						job_is_completed(t_job *job);
void					allocate_job_loop(int repere);
void					delete_job(t_job *job);

/*
** jocontrol / execution
*/

void					print_jc_info(t_job *job);
void					signal_print(int i);
char					**set_copy(t_myloc *env);
int						check_b(char **cmd);
void					if_not_cmd(char *cmd);
void					is_valid(char *str, const char *dst, DIR *ptr);
char					*is_b(char **cmd);
void					exec_prgrm(char **cmd, char *path);
void					norme(t_job *comp2, int i, t_job *save);
int						process_nb(t_process *pro);
int						execute_builtin(char **cmd);
void					save_fd(void);
void					reset_fd(void);
void					close_fd(void);
void					do_in_child(int oldlink[2],
						int newlink[2], char ***av);
t_job					*if_bg_stp(t_job *job, t_job *save);
t_job					*if_bg(t_job *job, t_job *save, char *av);
t_job					*if_parser(char **av, t_job *job);
t_job					*stopped_pgid(char **av, t_job *job);
void					manage_word(t_ast *ast);
void					go_left(t_ast *ast);
void					go_right(t_ast *ast);
void					manage_pipe(t_ast *ast);
void					manage_semic(t_ast *ast, int fg);
int						process_nb(t_process *pro);
int						process_status(pid_t pid, int status, t_process *p);
int						check_if_stop(t_process *p, t_job *job);
void					to_do_if_stp(t_job *job, t_job *save, int i);
int						check_jb_nb();
void					set_id_sign(int foreground);
void					fill_pipe(int oldlink[2],
						int newlink[2], char ***av, int i);
t_process				*fill_jc_struc(pid_t pid,
						char *cmd, t_process *pro);
void					wait_for_job(t_process *pro, t_job *job, int fg);
char					*local_file(char *str);
pid_t					last_stp_job(t_job *job);
t_job					*put_last_stp(t_job *job, int i, int l);
char					*my_path(char **cmd, char **env);
int						tab_size(char **s);
char					**del_one(char **tabl, int pos);
char					**check_assign(char **ass);
char					**tab_copy(char **tabl);
void					close_fd_father(int oldlink[2], int newlink[2]);
void					no_param_jobs(t_job *j);
void					print_job_status(int i, t_job *j, t_job *f_job);
pid_t					jobs_parser(char *str, t_job *j);
void					job_error(const char *str);
int						job_is_completed(t_job *j);
pid_t					job_nb(int i, t_job *j);
void					print_pid(t_job *j);
int						ft_jobs(t_job *j, char **av);
t_process				*father_process(char **av, t_process *pro,
						int oldlink[2], int newlink[2]);
int						child_process(int oldlink[2], int newlink[2],
						char *mypath, char **cmd);
void					put_last_fg(t_job *job, int i, int l);
void					do_to_ast();
void					update_bg_status();
int						check_if_stop(t_process *p, t_job *job);
int						process_status(pid_t pid, int status, t_process *p);
int						put_in_bg(t_job *job,
						int cont, char **av, t_process *pro);
t_job					*right_job(int cont, char **av, t_job *job);
t_job					*put_last_stp(t_job *job, int i, int l);
t_job					*stopped_pgid(char **av, t_job *job);
pid_t					last_stp_job(t_job *j);
pid_t					job_nb(int i, t_job *j);
pid_t					jobs_parser(char *str, t_job *j);
void					wait_for_job(t_process *pro, t_job *job, int i);
int						put_in_fg(int cont, t_job *job, char **av);
int						pipe_exec(char ***av, int fg);
int						init_shell_sig();
t_process				*init_process_struct();
t_job					*init_job_struct();
void					launch_fg(int foreground);
void					ign_jb_sign(int i);
void					ft_freetab(char **s1);
char					*get_line(char **env);
char					**get_line2(char **env);
char					*get_pathh(char *nwav, char **path);

#endif
