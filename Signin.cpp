/*
Este Ficheiro serve para:

 - lidar com a rececao de dados de utlizador no registo
 - Guardar estesdados num ficheiro de texto
 - ler os dados deste ficheiro na funçao login

*/

#include <iostream>
#include <fstream>

using namespace std;


void vRegisto()
{

    struct Utilizador
    {
        string nome;
        string email;
        string password;
        int pontuacao;
        int highScore;
        int nJogos;
        int totalperguntas;
    };
        cout << "\nREgisto: ";
        cout << "\nNome: ";
        getline(cin, Utilizador.nome);
}