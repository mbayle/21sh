echo -e '\e[1m\nO ls \e[3;1;36m """""" : \e[23;24;0m'
ls """"""
echo -e '\e[1m\nO ls \e[3;1;36m "a"uteur : \e[23;24;0m'
ls "a"uteur
echo -e '\e[1m\nO ls \e[3;1;36m "a""teur"" : \e[23;24;0m'
ls "a""teur"
echo -e '\e[1m\nO ls \e[3;1;36m "a""teur"lol : \e[23;24;0m'
ls "a""teur"lol
echo -e '\e[1m\nO ls \e[3;1;36m "a""teur"lol mdr : \e[23;24;0m'
ls "a""teur"lol mdr
echo -e '\e[1m\nO ls \e[3;1;36m "a teur"lol lol : \e[23;24;0m'
ls "a uteur"lol lol
echo -e '\e[1m\nO ls \e[3;1;36m "a" "teur"lol lol : \e[23;24;0m'
ls "a" "teur"lol lol
echo -e '\e[1m\nO ls \e[3;1;36m hi"a teur"lol lol : \e[23;24;0m'
ls hi"a teur"lol lol
echo -e '\e[1m\nO ls \e[3;1;36m hi "a teur"lol lol : \e[23;24;0m'
ls hi "a teur"lol lol
echo -e '\e[1m\nO ls \e[3;1;36m " "ateur"lol" lol : \e[23;24;0m'
ls " "ateur"lol" lol
echo -e '\e[1m\nO ls \e[3;1;36m """"a teur"lol lol" : \e[23;24;0m'
ls """"a teur"lol lol"
echo -e '\e[1m\nO ls \e[3;1;36m "a t"eur"lol lol"" : \e[23;24;0m'
ls "a t"eur"lol lol"
echo -e '\e[1m\nO ls \e[3;1;36m "auteur ; ls "no "&" yes : \e[23;24;0m'
ls "auteur ; ls "no "&" yes
echo -e '\e[1m\nO ls \e[3;1;36m "aut|eur"lol lol | pwd : \e[23;24;0m'
ls "aut|eur"lol lol | pwd
echo -e '\n        \e[41m --------------  \e[0m'
echo -e '\e[1m\nO echo \e[3;1;36m'  \\\' ': \e[23;24;0m'
echo \'
echo -e '\e[1m\nO echo \e[3;1;36m'  \\\\\\\\\\\' ': \e[23;24;0m'
echo \\\'
echo -e '\e[1m\nO echo \e[3;1;36m'  \\\\\\\\\\\" ': \e[23;24;0m'
echo \\\"
echo -e '\e[1m\nO echo \e[3;1;36m'  \'\\\\\\\' ': \e[23;24;0m'
echo '\\'
echo -e '\e[1m\nO echo \e[3;1;36m'  \\\\\\ ': \e[23;24;0m'
echo \\
echo -e '\e[1m\nO echo \e[3;1;36m' \'\\\\\\\\\\\\\\\' ': \e[23;24;0m'
echo '\\\\'
echo -e '\e[1m\nO echo \e[3;1;36m' \\\\\\\\\\\\\\ ': \e[23;24;0m'
echo \\\\
echo -e '\e[1m\nO echo \e[3;1;36m' \\\"\\\\\\\\\\\\\\ ': \e[23;24;0m'
echo \"\\\\

echo -e '\n        \e[41m --------------  \e[0m'
echo -e '\e[1m\nO echo \e[3;1;36m ${PATH}__${HOME} && echo I print  : \e[23;24;0m'

echo ${PATH}__${HOME} && echo I print
echo -e '\e[1m\nO echo \e[3;1;36m ${PATH} ${HOME} && echo I print  : \e[23;24;0m'
echo ${PATH} ${HOME} && echo I print
echo -e '\e[1m\nO echo \e[3;1;36m ${PATH} ;  ${HOME} ;  echo I print  : \e[23;24;0m'
echo ${PATH}  ; ${HOME} ;  echo I print
echo -e '\e[1m\nO echo \e[3;1;36m ${PATH} ;  "${HOME}" ;  echo I print  : \e[23;24;0m'
echo ${PATH}  ; "${HOME}" ;  echo I print
echo -e '\e[1m\nO echo \e[3;1;36m ${PATH} ; '\''${HOME}'\' ' ;  echo I print  : \e[23;24;0m'
echo ${PATH}  ; '${HOME}' ;  echo I print
echo -e '\e[1m\nO echo \e[3;1;36m '\''${PATH} ; ${HOME} ;  echo I print'\'' : \e[23;24;0m'

echo '${PATH}  ; ${HOME} ;  echo I print'
echo -e '\e[1m\nO echo \e[3;1;36m '\\\$'{PATH} ;  \"${HOME}\" ;  echo I print  : \e[23;24;0m'
echo \${PATH}  ; \"${HOME}\" ;  echo I print
