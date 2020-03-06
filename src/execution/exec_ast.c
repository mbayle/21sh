#include "projectinclude.h"

void    manage_word(t_ast *ast)
{
	allocate_job_loop(0);
	simple_exec(ast);
}

void    go_left(t_ast *ast)
{
	t_ast   *tmp;

	tmp = ast->left;
	check_op(tmp);
}

void    go_right(t_ast *ast)
{
	t_ast   *tmp;

	tmp = ast->right;
	check_op(tmp);
}

void    manage_semic(t_ast *ast, int fg)
{
	if (fg == 0)
		g_jobcontrol.g_fg = 0;
	go_left(ast);
	g_jobcontrol.g_fg = 1;
	go_right(ast);
}

void    manage_pipe(t_ast *ast)
{
	int p_pos;

	g_jobcontrol.sim = 1;
	allocate_job_loop(0);
	p_pos = 0;
	if (ast->right && ast->right->lex->operator != 3)
		p_pos = 1;
	go_left_pipe(ast, 0);
	go_right_pipe(ast, p_pos);
}
