#include "../../includes/projectinclude.h"

void		exec_clr3(char *str, int clr, int i, int m)
{
	if (i && (m = m + 10))
		clr_shell(clr);
	else
		ft_putstr(WHITE);
	es7(str, m);
}

static void	exec_clr2_b(int clr, int m)
{
	if (!clr)
		exec_clr3("> Blue 1 <", clr, 1, m + 45);
	else
		exec_clr3("Blue 1", clr, 0, m + 45);
	if (clr == 1)
		exec_clr3("> Blue 2 <\n", clr, 1, m + 45);
	else
		exec_clr3("Blue 2\n", clr, 0, m + 45);
	if (clr == 2)
		exec_clr3("> Red 1 <", clr, 1, m + 45);
	else
		exec_clr3("Red 1", clr, 0, m + 45);
	if (clr == 3)
		exec_clr3("> Red 2 <\n", clr, 1, m + 45);
	else
		exec_clr3("Red 2\n", clr, 0, m + 45);
	if (clr == 4)
		exec_clr3("> Green 1 <", clr, 1, m + 45);
	else
		exec_clr3("Green 1", clr, 0, m + 45);
	if (clr == 5)
		exec_clr3("> Green 2 <\n", clr, 1, m + 45);
	else
		exec_clr3("Green 2\n", clr, 0, m + 45);
}

static void	exec_clr2_b2(int clr, int m)
{
	if (clr == 7)
		ft_putstr(FYELLOW"                             > Yellow 2 <\n"WHITE);
	else
		ft_putstr("                   Yellow 2\n");
	if (clr == 8)
		exec_clr3("> Magenta 1 <", clr, 1, m + 45);
	else
		exec_clr3("Magenta 1", clr, 0, m + 45);
	if (clr == 9)
		exec_clr3("> Magenta 2 <\n", clr, 1, m + 45);
	else
		exec_clr3("Magenta 2\n", clr, 0, m + 45);
	if (clr == 10)
		exec_clr3("> Cyan 1 <", clr, 1, m + 45);
	else
		exec_clr3("Cyan 1", clr, 0, m + 45);
	if (clr == 11)
		exec_clr3("> Cyan 2 <\n", clr, 1, m + 45);
	else
		exec_clr3("Cyan 2\n", clr, 0, m + 45);
	if (clr == 12)
		exec_clr3("> White <", clr, 1, m + 45);
	else
		exec_clr3("White", clr, 0, m + 45);
}

static void	exec_clr2_b3(int clr, int m)
{
	if (clr == 6)
	{
		ft_putchar('\n');
		ft_marge(m + 9);
		ft_2putstr("Valid command indicator                       ",
				YELLOW"> Yellow 1 <"WHITE);
	}
	else
		exec_clr3("Valid command indicator             Yellow 1",
				clr, 0, m + 9);
	ft_putchar('\n');
	ft_marge(m + 16);
}

void		exec_clr2(int m, int clr, int ci)
{
	ft_putchar('\n');
	es9("SHELL COLOR\n", m + 36);
	exec_clr2_b(clr, m);
	exec_clr2_b3(clr, m);
	if (ci)
	{
		ft_2putstr("< ", GREEN"On"WHITE);
		ft_putstr("/Off >");
	}
	else
	{
		ft_putstr("< On/");
		ft_2putstr(RED"Off"WHITE, " >");
	}
	exec_clr2_b2(clr, m);
	if (clr == 13)
		exec_clr3("> Grey <\n\n", clr, 1, m + 45);
	else
		exec_clr3("Grey\n\n", clr, 0, m + 45);
	clr_shell(clr);
	es7("You can also change the shell color with the shortcut f3/f4", m + 14);
	ft_putstr(WHITE);
}
