/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_interactive_shell.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 12:40:19 by ymarcill          #+#    #+#             */
/*   Updated: 2020/03/11 02:35:32 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

void	sig_handler(int i)
{
	if (i == SIGINT || i == SIGTERM || i == SIGKILL)
	{
		reset_attr();
		exit(128 + i);
	}
	else if (i == SIGCONT)
		init_shell_sig();
}

void	ign_jb_sign(int i)
{
	sig_t	func;

	func = SIG_IGN;
	if (i)
		func = SIG_DFL;
	signal(SIGINT, sig_handler);
	signal(SIGKILL, sig_handler);
	signal(SIGTERM, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTSTP, func);
	signal(SIGTTIN, func);
	signal(SIGTTOU, func);
	signal(SIGCONT, sig_handler);
}

int		init_shell_sig(void)
{
	g_jobcontrol.shell_is_int = isatty(0);
	if (g_jobcontrol.shell_is_int)
	{
		while (tcgetpgrp(0) != (g_jobcontrol.shell_pgid = getpgrp()))
			kill(-(g_jobcontrol.shell_pgid), SIGTTIN);
		ign_jb_sign(0);
		g_jobcontrol.shell_pgid = getpid();
		if (setpgid(g_jobcontrol.shell_pgid, g_jobcontrol.shell_pgid)
			< 0)
		{
			ft_putstr_fd("Could not put the shell in its own process group", 2);
			return (0);
		}
		tcgetattr(0, &g_jobcontrol.term_attr);
		g_jobcontrol.save_attr = g_jobcontrol.term_attr;
		g_jobcontrol.term_attr.c_cc[VTIME] = 0;
		g_jobcontrol.term_attr.c_lflag &= ~(ICANON | ECHO | ISIG);
		g_jobcontrol.term_attr.c_cc[VMIN] = 1;
		tcsetattr(0, TCSANOW, &g_jobcontrol.term_attr);
		return (0);
	}
	return (g_jobcontrol.shell_is_int);
}

int		reset_attr(void)
{
	struct termios	term;

	if (isatty(0))
	{
		term = g_jobcontrol.save_attr;
		term.c_lflag |= ISIG;
		if (tcsetattr(0, TCSANOW, &term) == -1)
			return (-1);
	}
	return (0);
}
