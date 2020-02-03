#include "minishell.h"

int		welcome10(int m, t_struct s)
{
	ft_sleep(0);
	ft_putstr("###");
	fp("do", "do");
	do_m(m + 71);
	ft_sleep(0);
	ft_putstr("###");
	es8(m + 70, "###");
	sleep(2);
	tputs(tgetstr("cl", NULL), 1, ft_ptchar);
	tputs(tgetstr("ve", NULL), 1, ft_ptchar);
	print_prompt_bis(s.prompt, &s, 0);
	return (1);
}
