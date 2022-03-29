Bugs conhecidos: o locale pode não funcionar em sua máquina. O locale foi utilizado da mesma forma que mostrada nos slides disponibilizados pelo professor. O setLocale() global não estava funcionando, então foi usado o .imbue(locale("pt_BR.UTF-8")).

Se o locale estiver dando problema, pode-se comentar as linhas em Relatorio.cpp.

Linha 231
Linha 298
Linha 347

Caso isso seja feito, as porcentagens terão separador decimal como ponto ao invés de vírgula.
