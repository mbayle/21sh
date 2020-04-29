/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:38:50 by geargenc          #+#    #+#             */
/*   Updated: 2020/04/29 00:35:19 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

char				*ft_tilde_alone(void)
{
	char			*path;
	struct passwd	*pw;
	char			*tmp;

	path = get_myenv("HOME");
	if (!path)
	{
		tmp = getlogin();
		if (tmp)
		{
			pw = getpwnam(getlogin());
			if (pw)
				path = ft_strdup(pw->pw_dir);
		}
	}
	return (path);
}

char				*ft_tilde_user(t_txtlist *txt)
{
	char			*user;
	struct passwd	*pw;

	user = ft_strsub(txt->data, txt->start + 1, txt->len - 1);
	if (user)
	{
		pw = getpwnam(user);
		free(user);
		if (pw)
			return (ft_strdup(pw->pw_dir));
	}
	return (NULL);
}

int					ft_exp_tilde(t_txtlist *txt)
{
	char			*res;

	if (txt->data[txt->start + txt->len]
		&& txt->data[txt->start + txt->len] != '/'
		&& txt->data[txt->start + txt->len] != ':')
		return (ft_exp_text(txt));
	if (txt->len == 1)
		res = ft_tilde_alone();
	else if (txt->data[txt->start + 1] == '+')
		res = ft_getvar("PWD");
	else if (txt->data[txt->start + 1] == '-')
		res = ft_getvar("OLDPWD");
	else
		res = ft_tilde_user(txt);
	if (!res)
		return (ft_exp_text(txt));
	txt->data = res;
	return (0);
}
