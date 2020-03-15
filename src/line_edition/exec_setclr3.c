#include "../../includes/projectinclude.h"

void	anim_cpt2(int *lr, int *s, int m)
{
	while ((*lr)--)
		tputs(tgetstr("do", NULL), 1, ft_ptchar);
	*lr = *s;
	*s = m + 42;
	while ((*s)--)
		tputs(tgetstr("nd", NULL), 1, ft_ptchar);
	*s = *lr;
	tputs(tgetstr("sc", NULL), 1, ft_ptchar);
}
