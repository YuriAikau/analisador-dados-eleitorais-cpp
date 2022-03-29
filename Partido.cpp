#include "./Partido.h"

Partido::Partido(int numero_partido, int votos_legenda, const string& nome_Partido, const string& sigla_partido) {
    this->numero_partido = numero_partido;
    this->votos_legenda = votos_legenda;
    this->nome_Partido = nome_Partido;
    this->sigla_partido = sigla_partido;
    this->lista_candidatos = new list<Candidato*>();
    this->votos_nominais_totais = 0;
    this->candidatos_eleitos = 0;
    this->candidato_mais_votado = NULL;
}

void Partido::adicionaCandidato(Candidato* c) {
    this->lista_candidatos->push_back(c);
    
    c->setPartido(this);
    
    if(this->candidato_mais_votado == NULL) {
        this->candidato_mais_votado = c;
    }
    else if(c->getVotos_nominais() > this->candidato_mais_votado->getVotos_nominais()) {
        this->candidato_mais_votado = c;
    }
    else if(c->getVotos_nominais() == this->candidato_mais_votado->getVotos_nominais()) {
        if(c->getNumero() < this->candidato_mais_votado->getNumero()) {
            this->candidato_mais_votado = c;
        }
        else if(c->getData_nasc().compareTo(this->candidato_mais_votado->getData_nasc()) < 0) {
            this->candidato_mais_votado = c;
        }
    }
}

bool Partido::compareTo(Partido* p1, Partido* p2){
    int diff = (p2->getVotos_nominais()+p2->getVotos_legenda())-(p1->getVotos_nominais()+p1->getVotos_legenda());
    if (diff == 0){
        if(p2->getNumero_partido() < p1->getNumero_partido()){
            return false;
        }else{
            return true;
        }
    }
    return p2->getVotos_nominais()+p2->getVotos_legenda() < p1->getVotos_nominais()+p1->getVotos_legenda();
}

bool Partido::comparadorVotoLegenda(Partido* p1, Partido* p2){
    int diff1 = p2->getVotos_legenda() - p1->getVotos_legenda();
    if (diff1 == 0){
        int diff2 = p2->getVotos_nominais() - p1->getVotos_nominais();
        if(diff2 == 0){
            if(p2->numero_partido < p1->numero_partido){
                return false;
            }else{
                return true;
            }
        }
        return p2->getVotos_nominais() < p1->getVotos_nominais();
    }
    
    return p2->getVotos_legenda() < p1->getVotos_legenda();
}

bool Partido::comparadorMaisVotado(Partido* p1, Partido* p2){
    if(p1->getCandidato_mais_votado() == NULL) return false;
    if(p2->getCandidato_mais_votado() == NULL) return true;

    int diff = p2->getCandidato_mais_votado()->getVotos_nominais() - p1->getCandidato_mais_votado()->getVotos_nominais();
        if(diff == 0){
            if (p2->getCandidato_mais_votado()->getData_nasc().compareTo(p1->getCandidato_mais_votado()->getData_nasc()) < 0){
                return false;
            }else{
                return true;
            }
        }
    return p2->getCandidato_mais_votado()->getVotos_nominais() < p1->getCandidato_mais_votado()->getVotos_nominais();
}