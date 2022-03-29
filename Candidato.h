#ifndef CANDIDATO_H
#define CANDIDATO_H

#include <iostream>
#include <string>
#include <list>

#include "./Partido.h"

class Partido;

using namespace std;

typedef struct Calendar_t {
    int dia;
    int mes;
    int ano;
    int compareTo(const Calendar_t c) const;
} Calendar;

class Candidato{

    private:
        int numero;
        int votos_nominais;
        string situacao;
        string nome;
        string nome_urna;
        char sexo;
        Calendar data_nasc;
        string destino_voto;
        int numero_partido;
        Partido* partido;

    public:
    Candidato(int, int, const string&, const string&, const string&, char, const string&, const string&, int);

    int getNumero() const { return numero; }
    int getVotos_nominais() const { return votos_nominais; }
    const string& getSituacao() const { return situacao; }
    const string& getNome() const { return nome; }
    const string& getNome_urna() const { return nome_urna; }
    char getSexo() const { return sexo; }
    const Calendar& getData_nasc() const { return data_nasc; }
    const string& getDestino_voto() const { return destino_voto; }
    int getIdade(string idade) const;
    int getNumero_partido() const { return numero_partido; }
    const Partido* getPartido() const { return partido; }

    void setNumero(int numero) { this->numero = numero; }
    void setVotos_nominais(int votos_nominais) { this->votos_nominais = votos_nominais; }
    void setSituacao(const string& situacao) { this->situacao = situacao; }
    void setNome(const string& nome) { this->nome = nome; }
    void setNome_urna(const string& nome_urna) { this->nome_urna = nome_urna; }
    void setSexo(char sexo) { this->sexo = sexo; }
    void setData_nasc(const Calendar& data_nasc) { this->data_nasc = data_nasc; }
    void setDestino_voto(const string& destino_voto) { this->destino_voto = destino_voto; }
    void setNumero_partido(int numero_partido) { this->numero_partido = numero_partido; }
    void setPartido(Partido* partido) { this->partido = partido; }

    static bool compareTo(const Candidato* c1, const Candidato* c2);
    string to_string() const;

    ~Candidato() {}
};

// ostream& operator<<(ostream& os, const Candidato& c) { return os << c.to_string(); }

#endif