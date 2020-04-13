/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:45:41 by geargenc          #+#    #+#             */
/*   Updated: 2020/04/13 10:10:08 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projectinclude.h"

char		*getvar(char *var)
{
	t_lst2	*menv;

	menv = g_jobcontrol.s.env;
	while (menv)
	{
		if (ft_strcmp(menv->varn, var) == 0)
			return (menv->var == NULL ? ft_strdup("") : ft_strdup(menv->var));
		menv = menv->next;
	}
	return (NULL);
}

char		*ft_getvar(char *var)
{
	void	*ptr;

//	if (var && !ft_strcmp(var, "?"))
//		ptr = ft_spparam_qmark();
//	else
		ptr = ft_get_spparam(*var);
//	ft_putendl("ptr: ft_get_spparam: ");
//	ft_putendl((char*)var);
	if (ptr)
		return (((char *(*)(void))ptr)());
	//	return ((char *)ptr);
	ptr = getvar(var);
	if (ptr)
		return ((char *)ptr);
	return (NULL);
}

// Je te laisse improviser ici, me faut juste une chaine allouée a la fin pour que je puisse la free a l'arrivee
// Oui je crois de souvenir qu'en gros ft_getenv renvoyait juste la variable dans la memoire alors que get_var envoyait une copie...
// Au cas où tu te demandes, les premieres lignes servent a chercher les variables speciales comme $? donc faut garder :)
