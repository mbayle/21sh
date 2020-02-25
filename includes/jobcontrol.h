/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 11:30:26 by ymarcill          #+#    #+#             */
/*   Updated: 2020/02/20 00:43:58 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBCONTROL_H
# define JOBCONTROL_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/errno.h>
#include <dirent.h>

/*a process is a single process*/
typedef struct				s_process
{
	struct s_process		*next;
	char					*cmd;
	int						bin;
	pid_t					lpid;
	int						status;
	int						r_value;
	int						my_stdin;
	int						my_stdout;
	int						p_nb;

}							t_process;

/*a job is a pipeline of process*/
typedef struct				s_job
{
	struct s_process		*first_process;
	struct termios			j_mode;
//	struct s_process		*last_process;
	struct s_job			*next;
	char					*command;
	int						fg;
	int						j_nb;
	int						stop;
	int						completed;
	pid_t					pgid;
	int						last_j;
	int						last_ret;
}							t_job;

typedef struct				s_jobcontrol
{
	char					**env;
	struct termios			term_attr;
	struct termios			save_attr;
	struct s_job			*first_job;
	struct s_job			*first_mail;
	pid_t					shell_pgid;
	int						shell_is_int;
	int						repere;
	int						ret;
	int						g_fg;
}							t_jobcontrol;

typedef struct				s_read
{
	DIR						*ptr;
	struct dirent			*file;
	struct stat				rdbuf;
	char					*path;
	char					*tmp;

}							t_read;

struct s_jobcontrol				g_jobcontrol;

/**
 redir
 **/

void						redirect_to_file(char *file, mode_t mode, int stfd);

/**
parse ast
**/

char						**parse_redir(char *line, int exec);
/**
Utils
**/

int							reset_attr();
int							ft_occur(char const *s, char c);
char						*ft_strjoinnf(char const *s1, char const *s2);
char						*ft_strjoinfree(char *s1, char *s2);
int							ft_strlenu(char *str);
char						**quick_tab_cmd(char *line);
int							permissions(char **str, struct stat buf);
char						*ft_strdupn(char *str, char c);
char						*ft_strldup(char *str, char c);
/**
Manage job list
**/
int							job_is_completed(t_job *job);
void						allocate_job_loop(int repere);
void						delete_job(t_job *job);
/**
jocontrol
**/

void						do_to_ast();
void						update_bg_status();
int							check_if_stop(t_process *p, t_job *job);
int							process_status(pid_t pid, int status, t_process *p);
int							put_in_bg(t_job *job, int cont, char **av, t_process *pro);
t_job						*right_job(int cont, char **av, t_job *job);
t_job						*put_last_stp(t_job *job, int i, int l);
t_job						*stopped_pgid(char **av, t_job *job);
pid_t						last_stp_job(t_job *j);
pid_t						job_nb(int i, t_job *j);
pid_t						jobs_parser(char *str, t_job *j);
void						wait_for_job(t_process *pro, t_job *job, int i);
int							put_in_fg(int cont, t_job *job, char **av);
int							pipe_exec(char **av, char **env,  int fg);
int							init_shell_sig();
t_process					*init_process_struct();
t_job						*init_job_struct();
void						launch_fg(int foreground);
void						ign_jb_sign(int i);
void						ft_freetab(char **s1);
char						**get_line(char **env);
char						*get_pathh(char *nwav, char **path);


#endif
