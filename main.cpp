#include <iostream>
#include <string>

using namespace std;


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


int main()
{
    cout << "Hello";

    return 0;
}

int menu()
{
    int escolha = 0;

    while(escolha != 5){
    if (int login = 0){

    switch (escolha){
    case 1:
        //Iniciar jogo
        break;
    case 2:
        //Tabela de lideres
        break;
    case 3:
        //Eliminar utilizador
        break;
    case 4:
        //Sair
        break;
    default:
        //BRR! Erro
        break;}

    }else{

    switch (escolha){

    case 1:
        //Iniciar sessão
        break;
    case 2:
        //Registar
        break;
    case 3:
        //Iniciar jogo
        break;
    case 4:
        //Tabela de lideres
        break;
    case 5:
        //Sair
        break;
    default:
        //BRR! Erro
        break;
    }
    }
}
}