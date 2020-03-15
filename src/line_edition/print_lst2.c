#include "../../includes/projectinclude.h"

int		check_bracket2(t_struct s)
{
	int		c;
	int		i;
	char	stack[256];
	char	*str;

	i = 0;
	str = NULL;
	s.l = s.lbg;
	while (s.l && (i = i + 1))
		s.l = s.l->next;
	s.l = s.lbg;
	create_line(&str, &s, 0, i);
	c = ft_bracket(str, -1, 0, stack);
	if (c > -1)
		return (sec_free(&str, 0));
	return (sec_free(&str, c));
}

static char	*check_quotes3(int *d, int *s, char *c, char *save)
{
	if (*save == '\'' && (*c == *save || !*c))
	{
		if (*s)
			(*s)--;
		else
			(*s)++;
		if (!*s)
			*c = '\'';
		else
			*c = 0;
	}
	if (*save == '"' && (*c == *save || !*c))
	{
		if (*d)
			(*d)--;
		else
			(*d)++;
		if (!*d)
			*c = '"';
		else
			*c = 0;
	}
	save++;
	return (save);
}

static int	check_quotes2_b(t_struct st, char **str, int s)
{
	char	*save;
	int		d;
	char	c;
	int		r;

	(void)st;
	d = 1;
	c = 0;
	r = 0;
	save = *str;
	while (*save)
		if (*save == '\\')
			check_bslash(&save);
		else
			save = check_quotes3(&d, &s, &c, save);
	if (!s)
		r = -1;
	if (!d)
		r = -2;
	return (sec_free(str, r));
}

int			check_quotes_b(t_struct s)
{
	int		c;
	char	*l;

	c = 0;
	l = NULL;
	if (!s.lbg && !s.tmp)
		return (0);
	s.l = s.lbg;
	while (s.l && (c = c + 1))
		s.l = s.l->next;
	s.l = s.lbg;
	if (!(create_line(&l, &s, 0, c)))
		return (0);
	return (check_quotes2_b(s, &l, 1));
}
