#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>

void	exec_say(char **env)
{
	pid_t pid;
	char **tmp;

	tmp = malloc(sizeof(char*) *3);
	tmp[0]= "/usr/bin/say";
	tmp[1] = "Poisson d'avril ";
	tmp[2] = NULL;
	pid = fork();
	if (pid == 0)
		execve(tmp[0], tmp, env);
	else
		wait(NULL);
}

void	color_tail2()
{
	printf("\033[1m");
	printf("\033[40m");
	printf("\033[36mO");
}

void	color_tail1()
{
	printf("\033[1m");
	printf("\033[43m");
	printf("\033[30mO");
	
}
void	color_face2()
{
	printf("\033[1m");
	printf("\033[40m");
	printf("\033[34mø");
	
}

void	color_nag()
{
	printf("\033[1m");
	printf("\033[40m");
	printf("\033[34m(");
}

void	color_face()
{
	printf("\033[1m");
	printf("\033[40m");
	printf("\033[37mO");
}

void	color_lim()
{
	printf("\e[40m");
	printf("\e[34m|");
}

void	color_tail4()
{
	printf("\033[1m");
	printf("\033[42m");
	printf("\033[37mO");	
}

void	color_tail5()
{
	printf("\033[1m");
	printf("\033[45m");
	printf("\033[37mO");	
}

void	color_tail5bis()
{
	printf("\033[1m");
	printf("\033[40m");
	printf("\033[35mO");	
}
void	sea()
{
	printf("\033[44m");
	printf("\033[34m≈");
}

void	fish(int x, int y, int *screen)
{
	int	rep1 = screen[0] /3;
	int	rep2 = screen[1] / 4;

	if ((y == rep2*2 || y == rep2) && (x == rep1*2 + y || x == rep1*2 + y - 1 || x == rep1*2 + y - 2))
		color_face2();
	else if (x >= rep1 * 2)
	{
		if (x > rep1*2)
			color_face();
		else if (x == rep1*2)
			color_lim();
	}
	else
	{
		if ((y >= (rep2 + rep2 / 2) && y <= rep2*2)  && x >= (rep1 + rep1/2 - (y - (rep2 + rep2/2) + 1)) && x < rep1 + rep1/2)
			color_nag();
		else if ((y >= rep2*2 && y <= (rep2*2 + rep2/2) + 1)  && x >= ((((rep1 + rep1/2) - rep2/2) + (y- rep2*2) - 2)) && x < rep1 + rep1/2)
			color_nag();
		else if (y >= (rep2 + rep2/2) && y <= (rep2*2 + rep2/2) + 1 && x == rep1 + rep1/2)
			color_face();
		else if (y %2 == 0)
			color_tail5bis();
		else 
			color_tail2();
	}
}


void	fish_tail(int x, int y, int *screen, int up)
{
	int rep1 = screen[0] /3;;
	int rep2 = screen[1] / 4;;
	int check;

	if (!up)
	{
		if ((x == (((rep1 - rep2 * 2) - rep2) / 2) + (y - rep2)) || (x >  ((rep1 - rep2 * 2) - rep2) + (y - rep2) - 2) )
			color_tail5();
		else if (x > (y - rep2 - 0) && x < (((rep1 - rep2 * 2) - rep2) / 2) + (y - rep2))
			color_tail1();
		else if (x > (y - rep2 - 2) && x < (((rep1 - rep2 * 2) - rep2) / 2) + (y - rep2))
			color_tail4();
		else if (x > (y - rep2 - 6) && x < (((rep1 - rep2 * 2) - rep2) / 2) + (y - rep2))
			color_tail5();
		else if (x < (y - rep2 - 5))
				sea();
		else
			color_tail2();
	}
	else
	{
		if ((x == (((rep1 - rep2 * 2) - rep2) / 2) + (rep2*3 -y ))|| (x == (((rep1 - rep2 * 2) - rep2) + (rep2*3 -y) - 1)))
			color_tail5();
		else if (x > (rep2*3 - y + 2) && x < (((rep1 - rep2 * 2) - rep2) / 2) + (rep2*3 -y ))
			color_tail1();
		else if (x > (rep2*3 - y) && x < (((rep1 - rep2 * 2) - rep2) / 2) + (rep2*3 -y ))
			color_tail4();
		else if (x > (rep2*3 - y - 4) && x < (((rep1 - rep2 * 2) - rep2) / 2) + (rep2*3 -y ))
			color_tail5();
		else if (x <= rep2*3 - y- 4)
			sea();	
		else
			color_tail2();

	}
}

void	head(int x, int y, int *screen)
{
	int rep1 = screen[0] /3;
	int rep2 = screen[1] / 4;
	
	if (x < (rep1 -y) || x > (rep1 * 2) + y)
		sea();
	else
		fish(x, y, screen);
}

void	tail_head(int x, int y, int *screen)
{
	int rep1 = screen[0] /3;
	int rep2 = screen[1] / 4;
				
	if (x < ((rep1 - rep2 * 2) - rep2) + (y - rep2))
		fish_tail(x, y, screen, 0);
	else if ( x < (rep1 - y) ||  x > rep1 * 2 + y)
		sea();
	else 
		fish(x, y, screen);
}

void	tail_body(int x, int y, int *screen)
{
	int rep1 = screen[0] /3;
	int rep2 = screen[1] / 4;
	int	rep0 = rep2 * 4;

	if (x < ((rep1 - rep2 * 2) - rep2) + (rep2*3 -y ))
		fish_tail(x, y, screen, 1);
	else if (x < (rep1 - (rep0 - y)) || x > (rep1 * 2) + (rep0 - y))
		sea();
	else 
		fish(x, y, screen);
}

void	body(int x, int y, int *screen)
{
	int rep1 = screen[0] /3;
	int rep2 = screen[1] / 4;
	int	rep0 = rep2 *4;
	if (x < (rep1 - (rep0 - y)) || x > (rep1 * 2) + (rep0 - y))
		sea();
	else
		fish(x, y, screen);
}

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	struct	winsize	win;
	int		screen[2];
	int		x = 0;
	int		y = 0;
	int		rep0;
	int		rep1;
	int		rep2;

	ioctl(0, TIOCGWINSZ, &win);
	screen[0] = win.ws_col;
	screen[1] = win.ws_row;
	exec_say(env);
	rep2 = screen[1] / 4;;
	rep1 = screen[0] / 3;
	while (y < screen[1])
	{
		while (x < screen[0])
		{
			if (y >= 0 && y <= rep2)
				head(x, y, screen);
			else if (y > rep2 && y <= rep2 * 2)
				tail_head(x, y, screen);
			else if (y > rep2 * 2 && y <= rep2 *3)
				tail_body(x, y, screen);
			else if (y > rep2 *3 && y <= rep2 *4)
				body(x, y, screen);
			x++;
		}
		printf("\r\n");
		x = 0;
		y++;
	}
	return (0);
}
