/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_interactive_shell.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 12:40:19 by ymarcill          #+#    #+#             */
/*   Updated: 2020/02/20 01:16:39 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

void	ign_jb_sign(int i)
{
	sig_t	func;

	func = SIG_IGN;
	if (i)
		func = SIG_DFL;
	signal(SIGINT, func);
	signal(SIGQUIT, func);
	signal(SIGTSTP, func);
	signal(SIGTTIN, func);
	signal(SIGTTOU, func);
}

int		init_shell_sig()
{
	if ((g_jobcontrol.shell_is_int = isatty(0)))
	{
		while (tcgetpgrp(0) != (g_jobcontrol.shell_pgid = getpgrp()))
			kill(-(g_jobcontrol.shell_pgid), SIGTTIN);
		ign_jb_sign(0);
		if (setpgid(g_jobcontrol.shell_pgid = getpid(), g_jobcontrol.shell_pgid) < 0)
		{
			ft_putstr_fd("Could not put the shell in its own process group", 2);
			return (0);
		}
		tcgetattr(0, &g_jobcontrol.term_attr);
		g_jobcontrol.save_attr = g_jobcontrol.term_attr;
		g_jobcontrol.term_attr.c_cc[VTIME] = 0;
		g_jobcontrol.term_attr.c_lflag &= ~(ICANON | ECHO );//| ISIG);
		g_jobcontrol.term_attr.c_cc[VMIN] = 1;
		tcsetattr(0, TCSANOW, &g_jobcontrol.term_attr);
		return (0);
	}
	return (g_jobcontrol.shell_is_int);
}

int		reset_attr()
{
	struct termios	term;
	
	if (isatty(0))
	{
		term = g_jobcontrol.save_attr;
   		if (tcsetattr(0, TCSANOW, &term) == -1)
        	return (-1);
	}
	return (0);
}
