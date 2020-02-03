#include "minishell.h"

void	welcome5(int m)
{
	ft_putchar('#');
	do_m(m + 8);ft_putchar('#');
	fp("up", NULL);
	ft_sleep(0);
	ft_putchar('#');
	do_m(m + 9);ft_putchar('#');
	fp("up", NULL);
	ft_sleep(0);
	ft_putchar('#');
	do_m(m + 10);ft_putchar('#');
	fp("up", NULL);
	ft_sleep(0);
	ft_putchar('#');
	do_m(m + 11);
	ft_sleep(0);
	ft_putchar('#');
	fp("up", NULL);
	ft_sleep(0);
	ft_putchar('#');
	do_m(m + 12);
	ft_sleep(0);
	ft_putchar('#');
	fp("up", NULL);
	ft_sleep(0);
	ft_putchar('#');
}

void	welcome6(int m)
{
	do_m(m + 13);
	ft_sleep(0);
	ft_putchar('#');
	fp("up", NULL);
	ft_sleep(0);
	ft_putchar('#');
	do_m(m + 14);
	ft_sleep(0);
	ft_putchar('#');
	fp("up", NULL);
	ft_sleep(0);
	ft_putchar('#');
	do_m(m + 15);
	ft_sleep(0);
	ft_putchar('#');
	fp("up", NULL);
	ft_sleep(0);
	ft_putchar('#');
	do_m(m + 16);
	ft_sleep(0);
	ft_putchar('#');
	fp("up", NULL);
	ft_sleep(0);
	ft_putchar('#');
	fp("do", NULL);
}

void	welcome7(int m)
{
	es8(m + 12, "####");
	es8(m + 11, "####");
	es8(m + 10, "####");
	fp("up", NULL);
	fp("up", NULL);
	fp("up", NULL);
	fp("up", NULL);
	fp("up", NULL);
	ft_sleep(0);
	ft_putstr("#####");
	fp("up", "le");
	fp("le", "le");
	fp("le", NULL);
	ft_sleep(0);
	ft_putstr("#####");
	fp("up", "le");
	fp("le", "le");
	fp("le", NULL);
	ft_sleep(0);
	ft_putstr("#####");
	fp("up", "le");
	fp("le", "le");
	fp("le", NULL);
	ft_sleep(0);
	ft_putstr("#####");
}

void	welcome8(int m)
{
	fp("do", NULL);
	do_m(m + 25);
	ft_sleep(0);
	ft_putstr("###");
	fp("up", "le");
	ft_sleep(0);
	ft_putstr("###");
	fp("up", "le");
	ft_sleep(0);
	ft_putstr("###");
	ft_putstr_anim("##########", 10);
	es8(m + 38, "####");
	es8(m + 36, "####");
	es8(m + 34, "####");
	es8(m + 32, "####");
	es8(m + 30, "####");
	es8(m + 28, "####");
	es8(m + 26, "####");
	es8(m + 24, "####");
	ft_putstr_anim("###########     ########", 24);
	fp("up", NULL);
	fp("le", "le");
	ft_sleep(0);
	ft_putstr("###");
	fp("up", "le");
}

void	welcome9(int m)
{
	fp("le", NULL);
	ft_sleep(0);
	ft_putstr("###");
	fp("up", "le");
	fp("le", NULL);
	ft_sleep(0);
	ft_putstr("###");
	fp("up", "le");
	fp("le", NULL);
	ft_sleep(0);
	ft_putstr("###");
	ft_putstr_anim("#####    ###", 12);
	es8(m + 64, "###");
	es8(m + 63, "###");
	es8(m + 62, "###");
	es8(m + 61, "###");
	fp("up", "up");
	fp("nd", "nd");
	ft_putstr_anim("#########", 9);
	fp("up", NULL);
	fp("le", "le");
	ft_sleep(0);
	ft_putstr("###");
	fp("up", "le");
	fp("le", NULL);
}
