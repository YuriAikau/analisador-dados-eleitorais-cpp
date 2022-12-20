#ifndef PARTIDO_H
#define PARTIDO_H

#include <iostream>
#include <list>
#include <stdbool.h>

#include "./Candidato.h"

class Candidato;

using namespace std;

class Partido {

    private:
        int numero_partido;
        int votos_legenda;
        string nome_Partido;
        string sigla_partido;
        list<Candidato*>* lista_candidatos;
        int votos_nominais_totais;
        int candidatos_eleitos;
        Candidato* candidato_mais_votado;

    public:

        Partido(int, int, const string&, const string&);

        const Candidato* getCandidato_mais_votado() const { return candidato_mais_votado; }
        int getNumero_partido() const { return numero_partido; }
        int getVotos_legenda() const { return votos_legenda; }
        const string getNome_Partido() const { return nome_Partido; }
        const string getSigla_partido() const { return sigla_partido; }
        list<Candidato*>* getLista_candidatos() { return lista_candidatos; }
        int getVotos_nominais() const { return this->votos_nominais_totais; }
        int getCandidatos_eleitos() const { return this->candidatos_eleitos; }

        void setCandidato_mais_votado(Candidato*& candidato_mais_votado) { this->candidato_mais_votado = candidato_mais_votado; }
        void setNumero_partido(int numero_partido) { this->numero_partido = numero_partido; }
        void setVotos_legenda(int votos_legenda) { this->votos_legenda = votos_legenda; }
        void setNome_Partido(const string& nome_Partido) { this->nome_Partido = nome_Partido; }
        void setSigla_partido(const string& sigla_partido) { this->sigla_partido = sigla_partido; }

        void adicionaCandidato(Candidato*);
        void addVotos_nominais(int valor) { this->votos_nominais_totais += valor; }
        void addCandidato_eleitos() { this->candidatos_eleitos++; }

        static bool compareTo(Partido* p1, Partido* p2);
        static bool comparadorVotoLegenda(Partido* p1, Partido* p2);
        static bool comparadorMaisVotado(Partido* p1, Partido* p2);

        string to_string() const { return this->sigla_partido + " - " + std::to_string(this->numero_partido) + ", "; }

        ~Partido() { delete this->lista_candidatos; }
};

// ostream& operator<<(ostream& os, const Partido& d) { return os << d.to_string(); }


#endif