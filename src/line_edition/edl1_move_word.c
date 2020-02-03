#include "minishell.h"

int		move_word(t_struct *s, int c)
{
	if (c == 67 || !s->lbg || c == 65 || c == 66)
		return (1);
	while (s->tmp->prev && !(check_whitespaces(s->tmp->prev->c)))
		s->tmp = s->tmp->prev;
	if (!(s->tmp->prev))
		s->lbg = NULL;
	else
		s->tmp = s->tmp->prev;
	return (1);
}
