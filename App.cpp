#include <iostream>
#include <map>
#include <stdlib.h>

#include "./Relatorio.h"

using namespace std;

int main(int argc, char** argv) {


    map<int, Partido*>* m = lePartidos(argv[2]);
    list<Candidato*>* c = leCandidatos(argv[1], m);
    geraRelatorio(c, m, argv[3]);
    
    deleteBoladao(m, c);

    return 0;
}