#include "minishell.h"

static int	delete_char(t_lst **lbg, t_lst **tmp)
{
	if (!(*tmp)->prev)
	{
		*tmp = (*tmp)->next;
		free((*tmp)->prev);
		(*tmp)->prev = NULL;
		*lbg = NULL;
		return (1);
	}
	if ((*tmp)->prev)
	{
		(*tmp)->prev->next = (*tmp)->next;
		*tmp = (*tmp)->prev;
		free((*tmp)->next->prev);
		(*tmp)->next->prev = *tmp;
	}
	return (1);
}

static int	move_cur2(t_lst **tmp, t_lst **lbg, char buf[5])
{
	if (buf[2] == 68 && *tmp)
	{
		if ((*tmp)->prev)
			*tmp = (*tmp)->prev;
		else
			*lbg = NULL;
	}
	if (buf[2] == 67 && (*tmp)->next)
		*tmp = (*tmp)->next;
	return (1);
}

static void	move_cur(t_lst **tmp, t_lst **lbg, char buf[5])
{
	if ((buf[2] == 65 || buf[2] == 70) && *tmp)
		while (*tmp && (*tmp)->next)
			*tmp = (*tmp)->next;
	if ((buf[2] == 66 || buf[2] == 72) && *tmp)
	{
		while (*tmp != *lbg)
			*tmp = (*tmp)->prev;
		*lbg = NULL;
	}
}



int			edit_line2(t_lst **lbg, t_lst **tmp, char buf[5])
{
	if (buf[0] == 27 && buf[1] == 27 && buf[2] == 91
	&& (buf[3] == 67 || buf[3] == 68 || buf[3] == 65 || buf[3] == 66))
		return (edl2_move_word(lbg, tmp, buf[3]));
	if ((buf[0] == 127 || (buf[0] == 27 && buf[3] == 126)))
		return (delete_char(&*lbg, &*tmp));
	if ((buf[0] == 27 && buf[1] == 91) && (buf[2] == 68 || buf[2] == 67
				|| buf[2] == 65 || buf[2] == 66 || buf[2] == 72 || buf[2] == 70))
	{
		if (*tmp && (buf[2] == 65 || buf[2] == 66 || buf[2] == 70 || buf[2] == 72))
			move_cur(&*tmp, &*lbg, buf);
		return (move_cur2(&*tmp, &*lbg, buf));
	}
	return (0);
}
