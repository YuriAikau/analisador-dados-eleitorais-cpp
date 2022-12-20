#include "./Relatorio.h"

#ifndef TAM
#define TAM 1000
#endif

static void splitPartidos(string*, string, int);
static void splitCandidatos(string*, string, int);

static void imprimeRelatorio6(list<Partido*>*);
static void imprimeRelatorio7(list<Partido*>*);
static void imprimeRelatorio8(list<Partido*>*);
static void imprimeRelatorio9e10(list<Candidato*>*, string);
static void imprimeRelatorio11(list<Partido*>*);

std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ") {
    str.erase(0, str.find_first_not_of(chars));
    return str;
}
 
std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ") {
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}
 
std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ") {
    return ltrim(rtrim(str, chars), chars);
}

map<int, Partido*>* lePartidos(char* destino) {
    map<int, Partido*>* mapPartidos = new map<int, Partido*>();
    
    FILE* f = fopen(destino, "r");

    if(f == NULL){
        cout << "Erro na abertura do arquivo" << endl;
        exit(1);
    }

    int n = 4;
    string data[n];
    char linha[TAM];

    fgets(linha,1000,f);

    while(fgets(linha,1000,f) && !(feof(f))) {
        
        splitPartidos(data,linha,n);

        int numero_partido = stoi(data[0]);
        int votos_legenda = stoi(data[1]);
        string nome_partido = data[2];
        string sigla_partido = data[3];

        Partido* partido = new Partido(numero_partido, votos_legenda, nome_partido, sigla_partido);
        mapPartidos->insert(pair<int, Partido*>(numero_partido, partido));
    }

    fclose(f);
    
    return mapPartidos;
}

list<Candidato*>* leCandidatos(char* destino, map<int,Partido*>* mapPartidos) {
    list<Candidato*>* listaCandidatos = new list<Candidato*>();
    
    FILE* f = fopen(destino, "r");

    if(f == NULL){
        cout << "Erro na abertura do arquivo" << endl;
        exit(1);
    }

    const unsigned int n = 9;
    string data[n];
    char linha[TAM];

    fgets(linha,1000,f);

    while(fgets(linha,1000,f) && !(feof(f))) {
        
        splitCandidatos(data,linha,n);

        int numero = stoi(data[0]);
        int votos_nominais = stoi(data[1]);
        string situacao = data[2];
        string nome = trim(data[3]);
        string nome_urna = trim(data[4]);
        char sexo = data[5].at(0);
        string data_nasc = data[6];
        string destino_voto = data[7];
        int numero_partido = stoi(data[8]);

        if(!destino_voto.compare("Válido")) {
            Candidato* candidato = new Candidato(numero, votos_nominais, situacao, nome, nome_urna, sexo, data_nasc, destino_voto, numero_partido);
            mapPartidos->at(numero_partido)->adicionaCandidato(candidato);
            mapPartidos->at(numero_partido)->addVotos_nominais(votos_nominais);
            listaCandidatos->push_back(candidato);
        }

        if(!situacao.compare("Eleito")) {
            mapPartidos->at(numero_partido)->addCandidato_eleitos();
        }
    }

    listaCandidatos->sort(Candidato::compareTo);

    fclose(f);
    
    return listaCandidatos;
}

void imprimeLista(list<Candidato*>* lista){
    int i = 1;
    for(Candidato* c : *lista){
        cout << i++ << " - " << c->to_string() << endl;
    }
}

void imprimeMapa(map<int, Candidato*>* mapa) {
    for(auto it = mapa->cbegin(); it != mapa->cend(); ++it)
        cout << it->first << " - " << it->second->to_string() << endl;
}

void geraRelatorio(const list<Candidato*>* listaCandidatos, const map<int,Partido*>* mapPartido, const string& data) {
    //Relatorio 1
        //Percorre toda a lista de candidatos para contar o total de eleitos, que eh igual ao total de vagas
        list<Candidato*>* listaCandidatosEleitos = new list<Candidato*>;

        int numeroVagas = 0;
        for(Candidato* temp: *listaCandidatos) {
            if(temp->getSituacao() == "Eleito") {
                listaCandidatosEleitos->push_back(temp);
                numeroVagas++;
            }
        }

        cout << "Número de vagas: " << numeroVagas << endl << endl;


        //Percorre toda a lista de candidatos e gera as listas para os relatorios de 2 a 5 (listas 1 a 4 respectivamente)
        list<Candidato*>* lista1 = new list<Candidato*>;
        list<Candidato*>* lista2 = new list<Candidato*>;
        map<int,Candidato*>* lista3 = new map<int,Candidato*>;
        map<int,Candidato*>* lista4 = new map<int,Candidato*>;
        
        int i = 1;
        for(Candidato* temp: *listaCandidatos) {
            if(temp->getSituacao() == "Eleito")
                lista1->push_back(temp);
            
            if(i <= numeroVagas)
                lista2->push_back(temp);
            
            if(i <= numeroVagas && ( temp->getSituacao() == "Suplente" || temp->getSituacao() == "Não eleito" ))
                lista3->insert(pair<int, Candidato*>(i,temp));
            
            if(i > numeroVagas && temp->getSituacao() == "Eleito")
                lista4->insert(pair<int, Candidato*>(i,temp));
            
            i++;
        }

        //Relatorio 2
        cout << "Vereadores eleitos:" << endl;
        imprimeLista(lista1);
        cout << endl;

        //Relatorio 3
        cout << "Candidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):" << endl;
        imprimeLista(lista2);
        cout << endl;

        //Relatorio 4
        cout << "Teriam sido eleitos se a votação fosse majoritária, e não foram eleitos:\n(com sua posição no ranking de mais votados)" << endl;
        imprimeMapa(lista3);
        cout << endl;

        //Relatorio 5
        cout << "Eleitos, que se beneficiaram do sistema proporcional:\n(com sua posição no ranking de mais votados)" << endl;
        imprimeMapa(lista4);
        cout << endl;

        //Cria uma lista de partidos a partir do mapa da partidos
        list<Partido*>* listaPartidos = new list<Partido*>;
        for(auto it = mapPartido->cbegin(); it != mapPartido->cend(); ++it)
            listaPartidos->push_back(it->second);

        //Relatorio 6
        imprimeRelatorio6(listaPartidos);

        //Relatorio 7
        imprimeRelatorio7(listaPartidos);
        //Relatorio 8
        imprimeRelatorio8(listaPartidos);

        // Relatorio 9 e 10
        imprimeRelatorio9e10(listaCandidatosEleitos, data);

        //Relatorio 11
        imprimeRelatorio11(listaPartidos);


        delete listaCandidatosEleitos;
        delete lista1;
        delete lista2;
        delete lista3;
        delete lista4;
        delete listaPartidos;
}

void imprimeRelatorio6(list<Partido*>* listaPartidos) {
    listaPartidos->sort(Partido::compareTo);
    
    int i = 1;
    cout << "Votação dos partidos e número de candidatos eleitos:" << endl;
    for(Partido* p: *listaPartidos)
        cout << i++ << " - " << p->to_string() << ((p->getVotos_nominais() + p->getVotos_legenda()) > 1 ?  std::to_string(p->getVotos_nominais() + p->getVotos_legenda()) + " votos (" : std::to_string(p->getVotos_nominais() + p->getVotos_legenda()) + " voto (") << (p->getVotos_nominais() > 1 ? std::to_string(p->getVotos_nominais())+ " nominais e " : std::to_string(p->getVotos_nominais()) + " nominal e ") << p->getVotos_legenda() << " de legenda), " << (p->getCandidatos_eleitos() > 1 ? std::to_string(p->getCandidatos_eleitos()) + " candidatos eleitos" : std::to_string(p->getCandidatos_eleitos()) + " candidato eleito") << endl;
}

void imprimeRelatorio7(list<Partido*>* lista) {
    lista->sort(Partido::comparadorVotoLegenda); 

    int i = 1;
    double numero;

    cout << "\nVotação dos partidos (apenas votos de legenda):" << endl;
    for(Partido* p: *lista) {
        
        stringstream stream;
        stream.imbue(locale("pt_BR.UTF-8"));

        string s;
        if((p->getVotos_legenda() + p->getVotos_nominais()) == 0){
            numero = 0.0;
            s = " (proporção não calculada, 0 voto no partido";
        }
        else{
            numero = (100 * p->getVotos_legenda() / (double) (p->getVotos_legenda() + p->getVotos_nominais()));
            stream << fixed << setprecision(2) << numero << "\% do total do partido";
            s = stream.str();
        }

        cout << i++ << " - " << p->to_string() << (p->getVotos_legenda() > 1 ? std::to_string(p->getVotos_legenda()) + " votos de legenda (" : std::to_string(p->getVotos_legenda()) + " voto de legenda") << s << ")" << endl;
    }
}

void imprimeRelatorio8(list<Partido*>* lista) {
    lista->sort(Partido::comparadorMaisVotado);

    int i = 1;
    cout << "\nPrimeiro e último colocados de cada partido:" << endl;

    for(Partido* p: *lista) {
        list<Candidato*>* tempList = p->getLista_candidatos();
        if(tempList->size() > 0){
            tempList->sort(Candidato::compareTo);
            Candidato* primeiro = tempList->front();
            Candidato* ultimo = tempList->back();

            if(primeiro->getDestino_voto() == "Válido" || ultimo->getDestino_voto() == "Válido") {
                cout << i++ << " - " + p->to_string();
                cout << primeiro->getNome_urna() + " (" + std::to_string(primeiro->getNumero()) + ", " + (primeiro->getVotos_nominais() > 1 ? std::to_string(primeiro->getVotos_nominais()) + " votos" : std::to_string(primeiro->getVotos_nominais()) + " voto") + ") / ";
                cout << ultimo->getNome_urna() << " (" << ultimo->getNumero() << ", " << (ultimo->getVotos_nominais() > 1 ? std::to_string(ultimo->getVotos_nominais()) + " votos)" : std::to_string(ultimo->getVotos_nominais()) + " voto)") << endl;
            }
        }
    }
}

void imprimeRelatorio9e10(list<Candidato*>* listaCandidatosEleitos, string data) {
    int q1 = 0, q2 = 0, q3 = 0, q4 = 0, q5 = 0;
    int M = 0, F = 0;
    int total = listaCandidatosEleitos->size();
    int idadeTemp = 0;

    for(Candidato* c: *listaCandidatosEleitos) {
        idadeTemp = c->getIdade(data);
        //cout << "\n" << c->getData_nasc().dia << "/" << c->getData_nasc().mes << "/" << c->getData_nasc().ano << " idade: " << idadeTemp <<endl;
        
        if(idadeTemp < 30)
            q1++;
        else if(idadeTemp >= 30 && idadeTemp < 40)
            q2++;
        else if(idadeTemp >= 40 && idadeTemp < 50)
            q3++;
        else if(idadeTemp >= 50 && idadeTemp < 60)
            q4++;
        else
            q5++;

        if(c->getSexo() == 'F') F++;
        if(c->getSexo() == 'M') M++;
    }

    //Porcentagens para idades
    stringstream stream;    
    
    stream.imbue(locale("pt_BR.UTF-8"));
    stream << fixed << setprecision(2) << (100 * q1 / (double) total) << "%";
    string n1 = stream.str();
    stream.str("");

    stream << fixed << setprecision(2) << (100 * q2 / (double) total) << "%";
    string n2 = stream.str();
    stream.str("");

    stream << fixed << setprecision(2) << (100 * q3 / (double) total) << "%";
    string n3 = stream.str();
    stream.str("");

    stream << fixed << setprecision(2) << (100 * q4 / (double) total) << "%";
    string n4 = stream.str();
    stream.str("");
    
    stream << fixed << setprecision(2) << (100 * q5 / (double) total) << "%";
    string n5 = stream.str();
    stream.str("");

    //Porcentagens para sexo
    stream << fixed << setprecision(2) << (100 * F / (double) total) << "%";
    string nf = stream.str();
    stream.str("");
    stream << fixed << setprecision(2) << (100 * M / (double) total) << "%";
    string nm = stream.str();
    stream.str("");

    cout << "\nEleitos, por faixa etária (na data da eleição):" << endl;
    cout << "      Idade < 30: " << q1 << " (" << n1 << ")\n30 <= Idade < 40: " << q2 << " (" << n2 << ")\n40 <= Idade < 50: " << q3 << " (" + n3 + ")\n50 <= Idade < 60: " << q4 << " (" << n4 << ")\n60 <= Idade     : " << q5 << " (" << n5 << ")\n" << endl;

    cout << "Eleitos, por sexo:" << endl;
    cout << "Feminino:  " << F << " (" << nf << ")\nMasculino: " << M << " (" << nm << ")\n" << endl;
}
    
void imprimeRelatorio11(list<Partido*>* listaPartidos) {
    int somaNominais = 0, somaLegenda = 0, somaTotal = 0;
    
    for(Partido* p : *listaPartidos) {
        somaNominais += p->getVotos_nominais();
        somaLegenda += p->getVotos_legenda();
    }
    somaTotal = somaNominais + somaLegenda;

    //Formato para as porcentagens do relatorio
    stringstream stream;

    //Porcentagens para as impressoes
    stream.imbue(locale("pt_BR.UTF-8"));
    stream << fixed << setprecision(2) << (100 * somaNominais / (double) somaTotal) << "%";
    string n1 = stream.str();
    stream.str("");
    stream << fixed << setprecision(2) << (100 * somaLegenda / (double) somaTotal) << "%";
    string n2 = stream.str();
    stream.str();

    cout << "Total de votos válidos:    " << somaTotal << endl;
    cout << "Total de votos nominais:   " << somaNominais << " (" << n1 << ")" << endl;
    cout << "Total de votos de legenda: " << somaLegenda << " (" << n2 << ")\n" << endl;
}

static void splitPartidos(string* vetorString, string s, int n){
    //string* vetorString = new string[n];
    char temp[n][TAM];

    sscanf(s.c_str(),"%[^,],%[^,],%[^,],%[^\n]\n", temp[0],temp[1],temp[2],temp[3]);

    for(int i = 0; i < n; i++){
        vetorString[i] = temp[i];
    }

}

static void splitCandidatos(string* vetorString, string s, int n) {
    //string* vetorString = new string[n];
    char temp[n][TAM];

    sscanf(s.c_str(),"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7], temp[8]);

    for(int i = 0; i < n; i++){
        vetorString[i] = temp[i];
    }

}

void deleteBoladao(map<int, Partido*>* m, list<Candidato*>* c) {
    for(auto it = m->cbegin(); it != m->cend(); ++it)
        delete it->second;
    delete m;

    for(Candidato* a : *c)
        delete a;
    delete c;
}