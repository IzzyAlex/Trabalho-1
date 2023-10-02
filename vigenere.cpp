#include <iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <unordered_map>

using namespace std;

string criarChave(string chave, string texto){
    unsigned int i_chave = 0;

    for( unsigned int i = 0; i < texto.size(); i++ ){
        if(texto[i] >= 'a' && texto[i] <= 'z'){
            texto[i] = chave[i_chave];

            i_chave++;

            if(i_chave == chave.size())
                i_chave = 0;
        }
    }

    return texto;
}

string removerCaracteres(string texto) {
    string resultado = "";

    for (unsigned int i = 0; i < texto.size(); i++) {
        char caractere = texto[i];

        if (caractere >= 'a' && caractere <= 'z') {
            resultado += caractere;
        }
    }

    return resultado;
}

string lerArquivo(string nome){
    string leitura;
    string linha;
    ifstream arquivo;

    arquivo.open(nome);
    
    if (arquivo.is_open()){
        while (! arquivo.eof()){
            getline (arquivo, linha);
            leitura.append(linha);
        }
        arquivo.close();
    }

    else cout << "Erro"; 

    return leitura;
}


string cifrar(string chaveTexto, string texto, vector<vector<int>> campo){
    string cifrado;

    for(unsigned int i = 0; i < texto.size(); i++){
        if(texto[i] >= 'a' && texto[i] <= 'z'){
            int x, y;

            x = texto[i] - 'a';
            y = chaveTexto[i] - 'a';

            cifrado.push_back((char) (campo[y][x] + 'a' - 1));
        }
        else{
            cifrado.push_back(texto[i]);
        }
    }

    return cifrado;
}

string decifrar(string chaveTexto, string texto, vector<vector<int>> campo){
    string decifrado;

    for(unsigned int i = 0; i < texto.size(); i++){
        if(texto[i] >= 'a' && texto[i] <= 'z'){
            unsigned int x, y;

            y = chaveTexto[i] - 'a';

            for(unsigned int j = 0; j < 26; j ++){
                if(campo[y][j] == texto[i] - 'a' + 1)
                    x = j;
            }

            decifrado.push_back((char) (campo[0][x] + 'a' - 1));
        }
        else{
            decifrado.push_back(texto[i]);
        }
    }

    return decifrado;
}

int encontrarTamanhoChave(const std::string &textoCodificado) {
    int tamanhoTexto = textoCodificado.length();
    std::vector<int> frequenciaEspacamentos(21, 0); // Inicialize um vetor de frequência de espaçamentos

    // Percorra o texto codificado para encontrar espaçamentos
    for (int i = 0; i < tamanhoTexto - 2; i++) {
        if (textoCodificado[i] == textoCodificado[i + 1] && textoCodificado[i] == textoCodificado[i + 2]) {
            // Encontrou um grupo de três letras consecutivas
            int espacamento = i + 3;
            while (espacamento < tamanhoTexto && textoCodificado[i] == textoCodificado[espacamento]) {
                espacamento++;
            }
            if (espacamento <= 20) {
                frequenciaEspacamentos[espacamento]++;
            }
            i = espacamento - 1;
        }
    }

    // Encontre o espaçamento com a maior frequência
    int tamanhoChave = 1;
    int maiorFrequencia = 0;
    for (int i = 1; i <= 20; i++) {
        if (frequenciaEspacamentos[i] > maiorFrequencia) {
            tamanhoChave = i;
            maiorFrequencia = frequenciaEspacamentos[i];
        }
    }

    return tamanhoChave;
}

char encontrarLetra(int indice, vector<string> partes, int linguagem){
    vector<double> portugues = {14.63,1.04,3.88,4.99,12.57,1.02,1.30,1.28,6.18,0.40,0.02,2.78,4.74,5.05,10.73,2.52,1.20,6.53,7.81,4.34,4.63,1.67,0.01,0.21,0.01,0.47};
    vector<double> ingles = {8.167,1.492,2.782,4.253,12.702,2.228,2.015,6.094,6.966,0.153,0.772,4.025,2.406,6.749,7.507,1.929,0.095,5.987,6.327,9.056,2.758,0.978,2.360,0.150,1.974,0.074};
    vector<double> meu_texto;

    string vertical;
    char letra;
    int opcao = -1, deslocamentos = 0;
    
    for(unsigned int i = 0; i < partes.size(); i ++)
        vertical.push_back(partes[i][indice]);

    while(opcao != 0){
    
        for(int i = 0; i < 26 ; i++){
            int contagem = 0;
            for(auto j : vertical){
                if('a' + i == j)
                    contagem++;
            }

            meu_texto.push_back((contagem*100) / vertical.size());

        }

        cout << endl << endl;

        if (linguagem == 1)
            cout << "Texto\t|\tPortugues" << endl;
        else
            cout << "Texto\t|\tIngles" << endl;

        for(int i = 0; i < 26 ; i++){
            
            if(deslocamentos >= 0){
                if(i+deslocamentos < 26)
                    cout << (char) ('a' + i + deslocamentos) << " (" << meu_texto[i+deslocamentos] << "%)" << "\t|\t";
                else
                    cout << (char) ('a' + i + deslocamentos - 26) << " (" << meu_texto[i+deslocamentos+26] << "%)" << "\t|\t";
            }
            else{
                if(i+deslocamentos < 0){
                    cout << (char) ('a' + i + deslocamentos + 26) << " (" << meu_texto[i+deslocamentos+26] << "%)" << "\t|\t";
                }
                else
                    cout << (char) ('a' + i + deslocamentos) << " (" << meu_texto[i+deslocamentos] << "%)" << "\t|\t";
            }
            
            if (linguagem == 1)
                cout << (char) ('a' + i) << " (" << portugues[i] << "%)" << "\t|\t" << endl;
            else if (linguagem == 2)
                cout << (char) ('a' + i) << " (" << ingles[i] << "%)" << "\t|\t" << endl;
        }

        cout << "1. Deslocar para cima" << endl;
        cout << "2. Deslocar para baixo" << endl;
        cout << "3. Definir letra" << endl;
        cout << "Opcao: ";
        cin >> opcao;

        if(opcao == 1)
            deslocamentos++;
        else if(opcao == 2){
            if(deslocamentos > -25)
                deslocamentos--;
        }
        else if(opcao == 3){
            cout << "Digite a letra: " << endl;
            cin >> letra;
            return letra;
        }
    
    }
    
    return ' ';
}


void encontrarChave(string texto, vector<vector<int>> campo){
    vector<string> partes;
    string chave, auxTexto;

    int tamanho, linguagem = 0, sabetamanho = 0;

    auxTexto = texto;
    texto = removerCaracteres(texto);

    system("clear || cls");

    tamanho = encontrarTamanhoChave(texto);

    while(linguagem < 1 || linguagem > 2) {
        cout << "Qual a linguagem?" << endl;
        cout << "1. Portugues" << endl;
        cout << "2. Ingles" << endl;
        cin >> linguagem;
    }

    system("clear || cls");

    while(sabetamanho < 1 || sabetamanho > 2) {
        cout << "Você sabe o tamanho da chave?" << endl;
        cout << "1. Sim" << endl;
        cout << "2. Não" << endl;
        cin >> sabetamanho;
    } if (sabetamanho == 1) {
        cout << "Digite o tamanho da chave: ";
        cin >> tamanho;
    }

    cout << "O tamanho da chave é: " << tamanho << endl;

    for(int i = 0; i < tamanho; i++)
        chave.push_back(' ');

    while(texto.size() != 0){
        partes.push_back(texto.substr(0, tamanho));
        texto.erase(0, tamanho);
    }

    
    for(int i = 0; i < tamanho; i++){
        chave[i] = encontrarLetra(i, partes, linguagem);
    }
    
    

    cout << "A chave é: " << chave << endl << endl;

    
    string chaveTexto = criarChave(chave, auxTexto);

    string decifrado = decifrar(chaveTexto, auxTexto, campo);
    cout << "Mensagem decifrada:" << endl;
    cout << decifrado << endl;

}


int main (){ 

    int opcao;
    string chave, texto, chaveTexto;
    vector < vector<int>> campo;
    vector <int> alfabeto;

    for(int i = 1; i <= 26; i++)
        alfabeto.push_back(i);

    system("clear || cls");

    for(unsigned int i = 0; i < alfabeto.size(); i++){
        campo.push_back(alfabeto);
        alfabeto.push_back(alfabeto[0]);
        alfabeto.erase(alfabeto.begin());
    }

    


    while (opcao < 1 || opcao > 3){
        cout << "1. Cifrar mensagem" << endl;
        cout << "2. Decifrar mensagem" << endl;
        cout << "3. Atacar uma mensagem cifrada" << endl;

        cin >> opcao;
        
    }
    
    chave = lerArquivo("chave.txt");
    texto = lerArquivo("texto.txt");

    for( auto &i : texto)
        i = tolower(i);

    for( auto &i : chave)
        i = tolower(i);

    chaveTexto = criarChave(chave, texto);

    if (opcao == 1){
        string cifrado = cifrar(chaveTexto, texto, campo);
        cout << "Mensagem cifrada:" << endl;
        cout << cifrado << endl;
    }
    if (opcao == 2) {
        string decifrado = decifrar(chaveTexto, texto, campo);
        cout << "Mensagem decifrada:" << endl;
        cout << decifrado << endl;
    }
    if (opcao == 3){
        encontrarChave(texto, campo);
    }
    
    




    return 0;
}