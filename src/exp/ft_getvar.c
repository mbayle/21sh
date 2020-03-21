/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:45:41 by geargenc          #+#    #+#             */
/*   Updated: 2020/03/21 08:02:00 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char		*ft_getvar(char *var, t_42sh *shell)
{
	void	*ptr;
	char	*varenv;

	ptr = ft_get_spparam(*var);
	if (ptr)
		return (((char *(*)(t_42sh *))ptr)(shell));
	varenv = ft_strjoin(var, "="); // A partir de cette ligne tu peux faire comme tu sens...
	ptr = ft_getenv(shell->env, varenv, ft_strlen(varenv), NULL); // Ici cette fonction recherche la variable dans l'environnement
	free(varenv);
	if (ptr)
		return (ft_strdup(ptr));
	ptr = get_var(shell, var); // Ici dans les variables locales, Jordan avait séparé en deux listes donc fallait check les deux
	if (ptr)
		return ((char *)ptr);
	return (NULL);
}

// Je te laisse improviser ici, me faut juste une chaine allouée a la fin pour que je puisse la free a l'arrivee
// Oui je crois de souvenir qu'en gros ft_getenv renvoyait juste la variable dans la memoire alors que get_var envoyait une copie...
// Au cas où tu te demandes, les premieres lignes servent a chercher les variables speciales comme $? donc faut garder :)