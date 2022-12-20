#ifndef RELATORIO_H
#define RELATORIO_H

#include <string>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <map>
#include <iomanip>
#include <locale>
#include <sstream>

#include "./Candidato.h"
#include "./Partido.h"

class Candidato;
class Partido;

using namespace std;

map<int,Partido*>* lePartidos(char*);
list<Candidato*>* leCandidatos(char*, map<int,Partido*>*);
void geraRelatorio(const list<Candidato*>*, const map<int,Partido*>*, const string&);

void deleteBoladao(map<int, Partido*>*, list<Candidato*>*); 

#endif