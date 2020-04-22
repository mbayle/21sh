/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_global.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 01:51:22 by geargenc          #+#    #+#             */
/*   Updated: 2020/04/22 15:51:45 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GLOBAL_H

# define FT_GLOBAL_H

# include "projectinclude.h"

t_spparam			g_spparamtab[] =
{
	{'?', &ft_spparam_qmark},
	{'\0', NULL}
};

int					(*g_txttab[])(char *word, size_t *index,
					t_txtlist **current, bool *dquote) =
{
	&ft_parse_tilde,
	&ft_parse_var,
	&ft_parse_backslash,
	&ft_parse_quote,
	&ft_parse_text
};

int					(*g_exptab[])(t_txtlist *txt) =
{
	NULL,
	&ft_exp_text,
	&ft_exp_tilde,
	&ft_exp_var,
	&ft_exp_brace,
	&ft_exp_sub,
	&ft_exp_expr
};

int					g_intr;

t_class				g_classestab[] =
{
	{"[:alnum:]",
		"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"},
	{"[:alpha:]", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"},
	{"[:blank:]", " \t"},
	{"[:cntrl:]", "\x0\x1\x2\x3\x4\x5\x6\x7\x8\x9\xA\xB\xC\xD\xE\xF\x10\x11"
		"\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F\x7F"},
	{"[:digit:]", "0123456789"},
	{"[:graph:]", "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"},
	{"[:lower:]", "abcdefghijklmnopqrstuvwxyz"},
	{"[:print:]", " 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"},
	{"[:punct:]", "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"},
	{"[:space:]", " \t\n\r\v\f"},
	{"[:upper:]", "ABCDEFGHIJKLMNOPQRSTUVWXYZ"},
	{"[:xdigit:]", "0123456789ABCDEFabcdef"},
	{NULL, NULL}
};

t_getmatch			g_getmatchtab[] =
{
	&ft_getmatch_wcard,
	&ft_getmatch_qmark,
	&ft_getmatch_hook,
	&ft_getmatch_text
};

t_match				g_matchtab[] =
{
	&ft_match_end,
	&ft_match_text,
	&ft_match_wcard,
	&ft_match_qmark,
	&ft_match_hook,
	&ft_match_rhook
};

t_expparamfunc		g_expparamtab[] =
{
	{":-", &ft_expparam_cnminus},
	{"-", &ft_expparam_minus},
	{":=", &ft_expparam_cnequal},
	{"=", &ft_expparam_equal},
	{":?", &ft_expparam_cnqmark},
	{"?", &ft_expparam_qmark},
	{":+", &ft_expparam_cnplus},
	{"+", &ft_expparam_plus},
	{"%", &ft_expparam_pcent},
	{"%%", &ft_expparam_dpcent},
	{"#", &ft_expparam_sharp},
	{"##", &ft_expparam_dsharp},
	{"", &ft_expparam_nofunc},
	{NULL, NULL}
};

char				*g_aritoktab[] =
{
	"ARI_NONE",
	"ARI_DEC",
	"ARI_HEX",
	"ARI_OCT",
	"ARI_VAR",
	"ARI_PS",
	"ARI_MS",
	"ARI_MUL",
	"ARI_DIV",
	"ARI_MOD",
	"ARI_POW",
	"ARI_BW_AND",
	"ARI_BW_OR",
	"ARI_BW_XOR",
	"ARI_BW_NOT",
	"ARI_BS_LT",
	"ARI_BS_RT",
	"ARI_EQ",
	"ARI_NE",
	"ARI_LT",
	"ARI_GT",
	"ARI_LE",
	"ARI_GE",
	"ARI_AND",
	"ARI_OR",
	"ARI_NOT",
	"ARI_AS",
	"ARI_PS_AS",
	"ARI_MS_AS",
	"ARI_MUL_AS",
	"ARI_DIV_AS",
	"ARI_MOD_AS",
	"ARI_BW_AND_AS",
	"ARI_BW_OR_AS",
	"ARI_BW_XOR_AS",
	"ARI_BS_LT_AS",
	"ARI_BS_RT_AS",
	"ARI_DB_PS",
	"ARI_DB_MS",
	"ARI_PAR_LT",
	"ARI_PAR_RT",
	"ARI_MS_SIGN"
};

t_ariop				g_arioptab[] =
{
	{"<<=", ARI_BS_LT_AS},
	{">>=", ARI_BS_RT_AS},
	{"**", ARI_POW},
	{"<<", ARI_BS_LT},
	{">>", ARI_BS_RT},
	{"==", ARI_EQ},
	{"!=", ARI_NE},
	{"<=", ARI_LE},
	{">=", ARI_GE},
	{"&&", ARI_AND},
	{"||", ARI_OR},
	{"+=", ARI_PS_AS},
	{"-=", ARI_MS_AS},
	{"*=", ARI_MUL_AS},
	{"/=", ARI_DIV_AS},
	{"%=", ARI_MOD_AS},
	{"&=", ARI_BW_AND_AS},
	{"|=", ARI_BW_OR_AS},
	{"^=", ARI_BW_XOR_AS},
	{"++", ARI_DB_PS},
	{"--", ARI_DB_MS},
	{"+", ARI_PS},
	{"-", ARI_MS},
	{"*", ARI_MUL},
	{"/", ARI_DIV},
	{"%", ARI_MOD},
	{"&", ARI_BW_AND},
	{"|", ARI_BW_OR},
	{"^", ARI_BW_XOR},
	{"~", ARI_BW_NOT},
	{"<", ARI_LT},
	{">", ARI_GT},
	{"!", ARI_NOT},
	{"=", ARI_AS},
	{"(", ARI_PAR_LT},
	{")", ARI_PAR_RT},
	{NULL, ARI_NONE}
};

t_ari_cond			g_ari_condtab[] =
{
	&ft_ari_lex_op,
	&ft_ari_lex_blank,
	&ft_ari_lex_hex,
	&ft_ari_lex_oct,
	&ft_ari_lex_dec,
	&ft_ari_lex_var,
	&ft_ari_lex_illegal_char
};

t_ari_ast_data		g_ari_asttab[] =
{
	{NULL, NULL, 0, ARI_TYPE_NONE},
	{&ft_ari_conv_dec, &ft_ari_ast_value, 0, ARI_TYPE_VALUE},
	{&ft_ari_conv_hex, &ft_ari_ast_value, 0, ARI_TYPE_VALUE},
	{&ft_ari_conv_oct, &ft_ari_ast_value, 0, ARI_TYPE_VALUE},
	{&ft_ari_conv_var, &ft_ari_ast_value, 0, ARI_TYPE_VALUE | ARI_TYPE_VAR},
	{&ft_ari_conv_op, &ft_ari_ast_ps, 4, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_ms, 4, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_op, 5, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_op, 5, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_op, 5, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_op, 6, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_op, 3, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_op, 3, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_op, 3, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_value, 7, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_op, 3, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_op, 3, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_op, 2, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_op, 2, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_op, 2, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_op, 2, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_op, 2, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_op, 2, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_op, 1, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_op, 1, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_value, 7, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_as, 0, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_as, 0, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_as, 0, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_as, 0, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_as, 0, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_as, 0, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_as, 0, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_as, 0, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_as, 0, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_as, 0, ARI_TYPE_OP},
	{&ft_ari_conv_op, &ft_ari_ast_as, 0, ARI_TYPE_OP},
	{&ft_ari_conv_dbp, &ft_ari_ast_db, 7, ARI_TYPE_OP | ARI_TYPE_DB},
	{&ft_ari_conv_dbm, &ft_ari_ast_db, 7, ARI_TYPE_OP | ARI_TYPE_DB},
	{&ft_ari_conv_op, &ft_ari_ast_value, 0, ARI_TYPE_OP | ARI_TYPE_SUB},
	{&ft_ari_conv_op, &ft_ari_ast_par_rt, 0, ARI_TYPE_VALUE},
	{NULL, NULL, 7, ARI_TYPE_OP}
};

t_ari_exe			g_ari_exetab[] =
{
	NULL,
	ft_ari_exe_value,
	ft_ari_exe_value,
	ft_ari_exe_value,
	ft_ari_exe_var,
	ft_ari_exe_ps,
	ft_ari_exe_ms,
	ft_ari_exe_mul,
	ft_ari_exe_div,
	ft_ari_exe_mod,
	ft_ari_exe_pow,
	ft_ari_exe_bw_and,
	ft_ari_exe_bw_or,
	ft_ari_exe_bw_xor,
	ft_ari_exe_bw_not,
	ft_ari_exe_bs_lt,
	ft_ari_exe_bs_rt,
	ft_ari_exe_eq,
	ft_ari_exe_ne,
	ft_ari_exe_lt,
	ft_ari_exe_gt,
	ft_ari_exe_le,
	ft_ari_exe_ge,
	ft_ari_exe_and,
	ft_ari_exe_or,
	ft_ari_exe_not,
	ft_ari_exe_as,
	ft_ari_exe_ps_as,
	ft_ari_exe_ms_as,
	ft_ari_exe_mul_as,
	ft_ari_exe_div_as,
	ft_ari_exe_mod_as,
	ft_ari_exe_bw_and_as,
	ft_ari_exe_bw_or_as,
	ft_ari_exe_bw_xor_as,
	ft_ari_exe_bs_lt_as,
	ft_ari_exe_bs_rt_as,
	ft_ari_exe_db_ps,
	ft_ari_exe_db_ms,
	NULL,
	ft_ari_exe_par_rt,
	ft_ari_exe_ms_sign
};

#endif
