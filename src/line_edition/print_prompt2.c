#include "minishell.h"

static void	print_prompt_bis4(t_struct st, int i)
{
	ft_putstr(BLUE"~ ");
	if (st.set_cpt)
	{
		ft_putstr(GREEN);
		ft_putchar('>');
		ft_putnbr(st.cpt);
		ft_putchar('<');
	}
	else
	{
		ft_putchar('-');
		ft_putnbr(st.cpt);
		ft_putchar('-');
	}
	if (!i)
		ft_putstr(RED" > "WHITE);
	else
		ft_putstr(GREEN" > "WHITE);
}

static void	print_prompt_bis5(char *pw, char *h)
{
	if (pw)
	{
		h = pw;
		pw = ft_pstrback(pw);
		while (*pw != '/')
			pw--;
		if (pw != h)
			pw++;
		ft_putstr(pw);
	}
	else
		ft_putstr("Minishell");
	ft_putstr(" ");
}

static void	print_prompt_bis3(t_struct st, char *h, char *pw, int i)
{
	if ((pw && h) && strcmp(h, pw) == 0)
		print_prompt_bis4(st, i);
	else
	{
		ft_putstr(BLUE);
		print_prompt_bis5(pw, h);
		if (st.set_cpt)
		{
			ft_putstr(GREEN);
			ft_putchar('>');
			ft_putnbr(st.cpt);
			ft_putchar('<');
		}
		else
		{
			ft_putchar('-');
			ft_putnbr(st.cpt);
			ft_putchar('-');
		}
		if (!i)
			ft_putstr(RED" > "WHITE);
		else
			ft_putstr(GREEN" > "WHITE);
	}
}

int			print_prompt_bis(int p, t_struct *s, int i)
{
	char	*h;
	char	*pw;
	t_lst2	*st;
	t_lst2	*sa;

	(void)p;
	st = (*s).env;
	h = NULL;
	pw = NULL;
	sa = st;
	while (st)
	{
		if (ft_strcmp(st->varn, "HOME") == 0)
			h = st->var;
		if (ft_strcmp(st->varn, "PWD") == 0)
			pw = st->var;
		st = st->next;
	}
	st = sa;
	print_prompt_bis3(*s, h, pw, i);
	return (1);
}
