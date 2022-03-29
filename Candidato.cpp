#include "./Candidato.h"

#define TAM 10

int Calendar::compareTo(const Calendar c) const {
    if(this->ano < c.ano)
        return 1;
    else if(this-> ano > c.ano)
        return -1;
    else {
        if(this->mes < c.mes)
            return 1;
        else if(this->mes > c.mes)
            return -1;
        else {
            if(this->dia < c.dia)
                return 1;
            else if(this->dia > c.dia)
                return -1;
            else
                return 0;
        }
    }
}

Candidato::Candidato(int numero, int votos_nominais, const string& situacao, const string& nome, const string& nome_urna, char sexo, const string& data_nasc, const string& destino_voto, int numero_partido) {
    
    Calendar cal;

    sscanf(data_nasc.c_str(),"%d/%d/%d",&(cal.dia),(&cal.mes),(&cal.ano));
 
    this->numero = numero;
    this->votos_nominais = votos_nominais;
    this->situacao = situacao;
    this->nome = nome;
    this->nome_urna = nome_urna;
    this->sexo = sexo;
    this->data_nasc = cal;
    this->destino_voto = destino_voto;
    this->numero_partido = numero_partido;
}

int Candidato::getIdade(string idade) const{
    Calendar temp;

    sscanf(idade.c_str(),"%d/%d/%d",&temp.dia,&temp.mes,&temp.ano);

    if(this->data_nasc.mes < temp.mes){
        return (temp.ano) - this->data_nasc.ano;
    }else if((this->data_nasc.mes == temp.mes) && (this->data_nasc.dia < temp.dia)){
        return (temp.ano) - this->data_nasc.ano;
    }else{
        return (temp.ano-1) - this->data_nasc.ano;
    }
}

bool Candidato::compareTo(const Candidato* c1, const Candidato* c2){
    int diff = c2->votos_nominais - c1->votos_nominais;
    if (diff == 0){
        if(c2->data_nasc.ano < c1->data_nasc.ano){
            return false;
        }else{
            return true;
        }
    }
    return c2->votos_nominais < c1->votos_nominais;
}

string Candidato::to_string() const {
    return this->nome + " / " + this->nome_urna + " (" + this->partido->getSigla_partido() + ", " + (this->votos_nominais > 1 ? std::to_string(this->votos_nominais) + " votos" : std::to_string(this->votos_nominais) + " voto") + ")";
}