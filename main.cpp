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

void boasvindas()
{

    cout << "|=========================|" << endl;
    cout << "|====SEJA BEM-VINDO AO====|" << endl;
    cout << "|========QUIZ GAME========!" << endl;
    cout << "|=========================|" << endl;
    
    cout << "Prima qualquer tecla para continuar" << endl;
    cin.ignore();


}

int main()
{
    cout << "Hello";

    return 0;
}