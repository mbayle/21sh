/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 23:49:22 by frameton          #+#    #+#             */
/*   Updated: 2020/02/16 02:16:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

int			lst2_size(t_lst2 *l)
{
	int		c;

	c = 0;
	while (l)
	{
		l = l->next;
		++c;
	}
	return (c + 1);
}

static void	print_prompt4(t_struct *s, char *h, char *pw)
{
	g_lined ? s->cpt = g_lined->cpt : 0;
	clr_shell(s->clr);
	if (pw && (h = pw))
	{
		pw = ft_pstrback(pw);
		while (*pw != '/')
			pw--;
		if (pw != h)
			pw++;
		ft_putstr(pw);
		s->coprompt = ft_strlen(pw);
	}
	if (!pw && (s->coprompt = 9))
		ft_putstr("Minishell");
	ft_putstr(" -");
	ft_putnbr(s->cpt);
	ft_putchar('-');
	if (s->ci)
		ft_putstr(RED" > "WHITE);
	else
	{
		clr_shell(s->clr);
		ft_putstr(" > "WHITE);
	}
	s->coprompt = s->coprompt + 8;
}

static void	print_prompt3(char *h, char **pw, t_struct *s)
{
	char	*l;

	g_lined ? s->cpt = g_lined->cpt : 0;
	l = *pw;
	s->coprompt = 0;
	if ((*pw && h) && ft_strcmp(h, *pw) == 0)
	{
		clr_shell(s->clr);
		ft_putstr("~ -");
		ft_putnbr(s->cpt);
		ft_putchar('-');
		if (s->ci)
			ft_putstr(RED" > "WHITE);
		else
		{
			clr_shell(s->clr);
			ft_putstr(" > "WHITE);
		}
		s->coprompt = 9;
	}
	else
		print_prompt4(s, h, l);
	sec_free(pw, 0);
}

static void	print_prompt2(int p, t_lst2 *s, t_struct *st)
{
	char	*h;
	char	*pw;

	h = NULL;
	pw = NULL;
	(void)p;
	pw = getcwd(pw, PATH_MAX);
	while (s)
	{
		if (ft_strcmp(s->varn, "HOME") == 0)
			h = s->var;
		s = s->next;
	}
	print_prompt3(h, &pw, st);
}

int			print_prompt(int p, t_struct *s, int i)
{
	int		c;
	t_lst2	*tmp;

	c = lst2_size((*s).env);
	tmp = (*s).env;
	if (((*s).envi = (char**)malloc(sizeof(*(*s).envi) * c)) == NULL)
		return (0);
	while (tmp)
	{
		if (((*s).envi[i] = ft_mstrcpy((*s).envi[i], tmp->env)) == NULL)
			return (0);
		tmp = tmp->next;
		++i;
	}
	if ((*s).env_path)
		c = -1;
	free((*s).env_path);
	if (((*s).env_path = search_pathenv((*s).env)) == NULL)
		if (c == -1)
			ft_eputstr("Shell "MAGENTA"warning"
					WHITE": the PATH environment variable doesn't exist.\n\0");
	(*s).envi[i] = 0;
	print_prompt2(p, (*s).env, s);
	return (1);
}
