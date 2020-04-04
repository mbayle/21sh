Acces a ma structure dans les fichiers suivants (voir commentaire dans fichier) :
- ft_exp_spparam.c
- ft_expanse.c
- ft_getvar.c

J'ai remplace mes ft_malloc_exit par malloc_exit et je t'ai mis le code de ma fonction si tu veux l'utiliser ou juste regarder
pense bien a remplacer tous les malloc par malloc_exit, dans la libft aussi, le seul malloc restant doit etre celui dans malloc_exit !

J'ai commente les choses qui me paraissent ne servir a rien mais je ne les ai pas supprimees au cas ou.
D'ailleurs si tu veux tous les noms des signaux et tous les messages d'erreur correspondants ils sont encore dans ft_global.h.

Les fonctions que tu dois utiliser sont dans ft_expanse.c :

Pour faire les expansions des mots d'une commande tu utilises ft_command_to_args (je l'ai modifiee pour qu'elle ne prenne plus mon AST en parametre mais direct un char **).
Je crois bien que je free au fur et a mesure que je fais les expansions, donc pas besoin de free a part le resultat que je te renvoie.

Pour expandre juste un mot et sans field splitting utilise ft_simple_expanse

Voila j'espere que tout ira bien et qu'il n'y aura pas de bug, je fais l'expression ari de mon cote
Aussi quand ton assemblage j'aurai un petit truc a modifier mais je prefere laisser comme c'est tant que je ne peux pas tester...
